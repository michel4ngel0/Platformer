#include "Scene.h"
#include <iostream>

Scene::Scene() {
	object_count_ = 0;
}

Scene::~Scene() {
	for (auto& pointers : objects_)
		delete pointers.first;
}

void Scene::insert_object(Entity* object) {
	if (objects_.find(object) != objects_.end())
		return;

	aabb bounding_box;
	bounding_box.x_ = object->getPosition().x;
	bounding_box.y_ = object->getPosition().y;
	bounding_box.x_size_ = object->getTextureRect().width;
	bounding_box.y_size_ = object->getTextureRect().height;

	treePointer pointer = collision_tree_.insert(object, bounding_box);
	objects_.insert(std::make_pair(object, pointer));

	object_count_ += 1;
}

void Scene::remove_object(Entity* object) {
	auto iterator = objects_.find(object);

	if (iterator == objects_.end())
		return;

	collision_tree_.remove(iterator->second);
	objects_.erase(iterator);

	object_count_ -= 1;
}

void Scene::update_object(Entity* object) {
	auto iterator = objects_.find(object);

	if (iterator == objects_.end())
		return;

	aabb bounding_box;
	bounding_box.x_ = object->getPosition().x;
	bounding_box.y_ = object->getPosition().y;
	bounding_box.x_size_ = object->getTextureRect().width;
	bounding_box.y_size_ = object->getTextureRect().height;

	collision_tree_.update(iterator->second, bounding_box);
}

size_t Scene::size() const {
	return object_count_;
}

Scene::treeIterator Scene::get_close_objects(const aabb& bounds) const {
	return collision_tree_.find_range(bounds);
}

void Scene::draw_view(sf::RenderTarget& target, aabb& view) {
	sf::FloatRect view_rectangle((float)view.x_, (float)view.y_,
	                             (float)view.x_size_, (float)view.y_size_);
	target.setView(sf::View(view_rectangle));

	auto iterator = collision_tree_.find_range(view);
	
	//	Ignore objects outside of the FOV
	for (; iterator.is_valid(); ++iterator) {
		target.draw(*iterator);
		/* Debug */
		//std::cerr << "drawing " <<
		//             iterator->getPosition().x << ", " <<
		//             iterator->getPosition().y << std::endl;
	}
}

std::map<Entity*, Scene::treePointer>& Scene::get_objects() {
	return objects_;
}