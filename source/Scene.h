#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include "aabb-tree\aabb_tree.h"
#include "Entity.h"


class Scene {
private:
	typedef aabbTree<Entity>::pointer treePointer;
	typedef aabbTree<Entity>::iterator treeIterator;

	std::map<Entity*, treePointer> objects_;
	aabbTree<Entity> collision_tree_;
	size_t object_count_;

public:
	Scene();
	~Scene();

	void insert_object(Entity*);
	void remove_object(Entity*);
	void update_object(Entity*);

	size_t size() const;

	treeIterator get_close_objects(const aabb&) const;
	void draw_view(sf::RenderTarget&, aabb&);
	std::map<Entity*, treePointer>& get_objects();
};
