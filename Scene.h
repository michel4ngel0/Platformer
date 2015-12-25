#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include "aabb-tree\aabb_tree.h"


class Scene {
private:
	typedef aabbTree<sf::Sprite>::pointer treePointer;
	typedef aabbTree<sf::Sprite>::iterator treeIterator;

	std::map<sf::Sprite*, treePointer> objects_;
	aabbTree<sf::Sprite> collision_tree_;
	size_t object_count_;

public:
	Scene();
	~Scene();

	void insert_object(sf::Sprite*);
	void remove_object(sf::Sprite*);
	void update_object(sf::Sprite*);

	size_t size() const;

	treeIterator get_close_objects(sf::Sprite*, const aabb&) const;
	void draw_view(sf::RenderTarget&, aabb&);
	std::map<sf::Sprite*, treePointer>& get_objects();
};
