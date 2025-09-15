#include "scene.h"
#include "game_obj.h"

Scene::Scene()
{
	//auto root_prt = std::make_unique<GameObj>(Vector2(0, 0));
	//root = root_prt.get();
	root = new GameObj(Vector2(0, 0));
	root->set_ID("root");
	root->set_size({ _WIN_W_,_WIN_H_ });
	root->set_anchor_mode(AnchorMode::TOPLEFT);
	root->set_anchor_referent_mode(AnchorMode::TOPLEFT);

	auto background_prt = std::make_unique<GameObj>(Vector2(0, 0));
	background = background_prt.get();
	background->set_ID("background");
	background->set_size({ _WIN_W_,_WIN_H_ });
	background->set_anchor_mode(AnchorMode::CENTER);
	background->set_anchor_referent_mode(AnchorMode::CENTER);

	auto entity_prt = std::make_unique<GameObj>(Vector2(0, 0));
	entity = entity_prt.get();
	entity->set_ID("entity");
	entity->set_size({ _WIN_W_,_WIN_H_ });
	entity->set_anchor_mode(AnchorMode::CENTER);
	entity->set_anchor_referent_mode(AnchorMode::CENTER);

	auto ui_prt = std::make_unique<GameObj>(Vector2(0, 0));
	ui = ui_prt.get();
	ui->set_ID("ui");
	ui->set_size({ _WIN_W_,_WIN_H_ });
	ui->set_anchor_mode(AnchorMode::CENTER);
	ui->set_anchor_referent_mode(AnchorMode::CENTER);

	root->add_children(std::move(background_prt));
	root->add_children(std::move(entity_prt));
	root->add_children(std::move(ui_prt));
}

Scene::~Scene()
{
	std::cout << ID << "  ~Scene()" << std::endl;
	delete root;
	background = nullptr;
	ui = nullptr;
	entity = nullptr;
	root = nullptr;
}

void Scene::on_enter()
{

	std::cout << ID << "    Scene::on_enter()" << std::endl;
	pre_order_traversal(root, [&](GameObj* obj) {
		obj->on_enter();
		});
	if (_DE_BUG_)
	{
		// ResMgr::instance()->res_traversal();
		/*pre_order_traversal(root, [&](GameObj* obj) {
			SDL_FRect r = obj->get_FRect();
			std::cout << "obj   " << obj->get_ID() << std::endl <<
				"         x: " << r.x << "  y: " << r.y << "  w: " << r.w << "  h: " << r.h << std::endl;
			});*/
	}
}

void Scene::on_update(float delta)
{
	pre_order_traversal(root, [&](GameObj* obj) {
		obj->on_update(delta);
		});
}

void Scene::on_input(const SDL_Event& event)
{
	pre_order_traversal(root, [&](GameObj* obj) {
		obj->on_input(event);
		});
}

void Scene::on_render()
{
	pre_order_traversal(root, [&](GameObj* obj) {
		obj->on_render();
		});
}

void Scene::on_exit()
{
	if (_DE_BUG_)
	{
		std::cout << "Scene::on_exit" << std::endl;
	}
	pre_order_traversal(root, [&](GameObj* obj) {
		obj->on_exit();
		});
}

void Scene::set_ID(const std::string id)
{
	ID = id;
}

std::string Scene::get_ID()
{
	return ID;
}

GameObj* Scene::find_obj(std::string id)
{
	pre_order_traversal(root, [&](GameObj* obj) {
		if (obj->get_ID() == id)
		{
			return obj;
		}
		});
}
// 获取UI根节点
GameObj* Scene::get_ui_root()
{
	return root;
}

void Scene::pre_order_traversal(GameObj* current_node, const std::function<void(GameObj*)>& callback)
{
	if (!current_node) return;

	if (!current_node->get_display()) return;

	if (callback)
	{
		callback(current_node);
	}

	current_node->for_each_child([&](GameObj* node) {
		post_order_traversal(node, callback);
		});
}

void Scene::post_order_traversal(GameObj* current_node, const std::function<void(GameObj*)>& callback)
{
	if (!current_node) return;

	if (!current_node->get_display()) return;

	current_node->for_each_child([&](GameObj* node) {
		post_order_traversal(node, callback);
		});

	if (callback)
	{
		callback(current_node);
	}
}

void Scene::level_order_traversal(GameObj* current_node, const std::function<void(GameObj*)>& callback)
{
	if (!current_node) return;

	if (!current_node->get_display()) return;

	std::queue<GameObj*> q;

	q.push(current_node);

	while (!q.empty())
	{
		int length = q.size();
		for (int i = 0; i < length; i++)
		{
			GameObj* p = q.front();
			q.pop();
			if (callback)
			{
				callback(p);
			}
			p->for_each_child([&](GameObj* node) {
				if (node->get_display())
				{
					q.push(node);
				}
				});
		}
	}
}