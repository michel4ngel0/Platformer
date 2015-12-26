#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

constexpr double eps = 0.0000001;

struct aabb {
	double x_, y_;
	double x_size_, y_size_;

	double area() const;
	double hull_area(const aabb&) const;
	void hull(const aabb&);
	bool is_contained(const aabb&) const;
	bool overlaps(const aabb&) const;
	void scale(double);
};

template<typename T>
class aabbTree {
private:
	struct node {
		node(const aabb&, node*, node*, node*);
		node(const aabb&, node*, T*);
		~node();

		bool is_leaf() const;

		aabb rectangle_;
		node* parent_;
		union {
			node* left_;
			T* data_;
		};
		node* right_;
	};

public:
	aabbTree();
	~aabbTree();

	struct iterator {
	private:
		node* node_;
		aabb query_;

		iterator(node*, const aabb&);

		template<typename T>
		friend class aabbTree;
	public:
		bool is_valid() const;
		iterator& operator++();
		T& operator*() const;
		T* operator->();
	};

	struct pointer {
	private:
		node* node_;

		pointer(node*);

		template<typename T>
		friend class aabbTree;
	public:
		bool is_valid() const;
		T& operator*() const;
		T* const operator->() const;
	};

	pointer insert(T*, aabb&);
	bool remove(pointer&);		//	invalidate the pointer and iterators
	pointer update(pointer&, aabb&);	//	pointing to the same element
	iterator find_range(const aabb&) const;
	iterator end() const;

private:
	node* root_;
	double box_margin_ = 0.0;
};




template<typename T>
aabbTree<T>::node::node(const aabb& area,
						node* parent, node* left, node* right) :
	rectangle_(area), parent_(parent), left_(left), right_(right) {
}

template<typename T>
aabbTree<T>::node::node(const aabb& area,
						node* parent, T* data) :
	rectangle_(area), parent_(parent), data_(data), right_(nullptr) {
}

template<typename T>
aabbTree<T>::node::~node() {
	if (!is_leaf()) {
		delete left_;
		delete right_;
	}
}

template<typename T>
bool aabbTree<T>::node::is_leaf() const {
	return (right_ == nullptr);
}

template<typename T>
aabbTree<T>::iterator::iterator(node* n, const aabb& box) :
	node_(n), query_(box) {
}

template<typename T>
bool aabbTree<T>::iterator::is_valid() const {
	if (node_ == nullptr)
		return false;
	if (!node_->is_leaf())
		return false;

	return true;
}

template<typename T>
typename aabbTree<T>::iterator& aabbTree<T>::iterator::operator++() {
	node* prev = node_;
	node_ = node_->parent_;

	while (node_ != nullptr) {
		if (node_->is_leaf())
			break;

		if (prev == node_->parent_) {
			if (node_->left_->rectangle_.overlaps(query_)) {
				prev = node_;
				node_ = node_->left_;
			}
			else {
				//	skip left son
				prev = node_->left_;
			}
		}
		else if (prev == node_->left_) {
			if (node_->right_->rectangle_.overlaps(query_)) {
				prev = node_;
				node_ = node_->right_;
			}
			else {
				//	skip right son
				prev = node_->right_;
			}
		}
		else {
			prev = node_;
			node_ = node_->parent_;
		}
	}

	return (*this);
}

template<typename T>
T& aabbTree<T>::iterator::operator*() const {
	return *(node_->data_);
}

template<typename T>
T* aabbTree<T>::iterator::operator->() {
	return node_->data_;
}

template<typename T>
aabbTree<T>::pointer::pointer(node* n) :
	node_(n) {
}

template<typename T>
bool aabbTree<T>::pointer::is_valid() const {
	if (node_ == nullptr)
		return false;
	if (!node_->is_leaf())
		return false;

	return true;
}

template<typename T>
T& aabbTree<T>::pointer::operator*() const {
	return *(node_->data_);
}

template<typename T>
T* const aabbTree<T>::pointer::operator->() const {
	return node_->data_;
}

template<typename T>
aabbTree<T>::aabbTree() {
	root_ = nullptr;
}

template<typename T>
aabbTree<T>::~aabbTree() {
	delete root_;
}

template<typename T>
typename aabbTree<T>::pointer aabbTree<T>::insert(T* data, aabb& box) {
	//box.scale(1 + box_margin_); 
	
	if (root_ == nullptr) {
		root_ = new node(box, nullptr, data);
		return pointer(root_);
	}

	if (root_->is_leaf()) {
		node* new_leaf = new node(box, nullptr, data);
		node* new_root = new node(box, nullptr, new_leaf, root_);
		new_root->rectangle_.hull(root_->rectangle_);
		root_->parent_ = new_root;
		new_leaf->parent_ = new_root;
		root_ = new_root;
		
		return pointer(new_leaf);
	}

	node* current = root_;

	while (!current->is_leaf()) {
		if (!box.is_contained(current->rectangle_))
			current->rectangle_.hull(box);

		if (box.is_contained(current->left_->rectangle_)) {
			current = current->left_;
			continue;
		}
		if (box.is_contained(current->right_->rectangle_)) {
			current = current->right_;
			continue;
		}

		double left_area = box.hull_area(current->left_->rectangle_);
		double right_area = box.hull_area(current->right_->rectangle_);

		if (left_area < right_area)
			current = current->left_;
		else
			current = current->right_;
	}

	node* new_leaf = new node(box, nullptr, data);
	node* middle = new node(current->rectangle_, current->parent_, current, new_leaf);
	middle->rectangle_.hull(box);
	if (current->parent_->left_ == current)
		current->parent_->left_ = middle;
	else
		current->parent_->right_ = middle;
	current->parent_ = middle;
	new_leaf->parent_ = middle;

	current = middle;
	pointer result(new_leaf);

	return result;
}

template<typename T>
bool aabbTree<T>::remove(pointer& pt) {
	if (!pt.node_->is_leaf())
		return false;

	if (pt.node_->parent_ == nullptr) {
		delete root_;
		root_ = nullptr;
		pt.node_ = nullptr;
		return true;
	}

	node* current = pt.node_;
	node* parent = current->parent_;
	node* sibling;
	if (current == parent->left_)
		sibling = parent->right_;
	else
		sibling = parent->left_;

	sibling->parent_ = parent->parent_;
	if (parent->parent_ == nullptr) {
		root_ = sibling;
	}
	else {
		if (parent->parent_->left_ == parent)
			parent->parent_->left_ = sibling;
		else
			parent->parent_->right_ = sibling;
	}

	parent->left_ = parent->right_ = nullptr;
	delete(current);
	delete(parent);

	pt.node_ = nullptr;
	return true;
}

template<typename T>
typename aabbTree<T>::pointer aabbTree<T>::update(pointer& pt, aabb& bounding_box) {
	if (!pt.is_valid())
		return pt;

	T* data = &(*pt);
	aabb& box = pt.node_->rectangle_;
	
	if (!bounding_box.is_contained(box)) {
		if (remove(pt))
			pt = insert(data, bounding_box);
	}

	return pt;
}

template<typename T>
typename aabbTree<T>::iterator aabbTree<T>::find_range(const aabb& area) const {
	if (root_ == nullptr)
		return iterator(nullptr, area);
	if (!area.overlaps(root_->rectangle_))
		return iterator(nullptr, area);

	node* current = root_;
	
	while (!current->is_leaf())
		current = current->left_;

	if (current->rectangle_.overlaps(area)) {
		return iterator(current, area);
	}
	else {
		iterator result(current, area);
		++result;
		return result;
	}
}

template<typename T>
typename aabbTree<T>::iterator aabbTree<T>::end() const {
	return aabbTree<T>::iterator(nullptr, aabb());
}