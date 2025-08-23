#pragma once

#include "Camera.h"
#include "game_obj.h"

/*������-����*/
class Scene
{
public:
	Scene()
	{
		root = new GameObj({ 0,0 });
		root->set_size({ _WIN_W_,_WIN_H_ });
		root->set_anchor_mode(AnchorMode::TOPLEFT);
		root->set_parent_anchor_mode(AnchorMode::TOPLEFT);

		background = new GameObj({ 0,0 });
		background->set_size({ _WIN_W_,_WIN_H_ });
		background->set_anchor_mode(AnchorMode::CENTER);
		background->set_parent_anchor_mode(AnchorMode::CENTER);

		entity = new GameObj({ 0,0 });
		entity->set_size({ _WIN_W_,_WIN_H_ });
		entity->set_anchor_mode(AnchorMode::CENTER);
		entity->set_parent_anchor_mode(AnchorMode::CENTER);

		ui = new GameObj({ 0,0 });
		ui->set_size({ _WIN_W_,_WIN_H_ });
		ui->set_anchor_mode(AnchorMode::CENTER);
		ui->set_parent_anchor_mode(AnchorMode::CENTER);

		root->add_children(background);
		root->add_children(entity);
		root->add_children(ui);

	}

	~Scene()
	{
		traverse_delete(root);
	}

	/*������ʼ��*/
	void on_enter()
	{
		traverse_enter(root);
	}
	/*��������*/
	void on_update(float delta)
	{
		traverse_update(root, delta);
	}

	/*�������*/
	void on_input(const SDL_Event& event)
	{
		traverse_input(root, event);
	}

	/*��Ⱦ��ͼ*/
	void on_render()
	{
		traverse_render(root);
	}
	/*�˳�����*/
	void on_exit()
	{
		traverse_exit(root);
	}

public:
	// ��ȡUI���ڵ�
	GameObj* get_ui_root()
	{
		return root;
	}

	void traverse_enter(GameObj* current_node)
	{
		if (!current_node) return;

		if (!current_node->get_display()) return;

		current_node->on_render();

		for (GameObj* child : current_node->get_children())
		{
			traverse_enter(child);
		}
	}

	void traverse_exit(GameObj* current_node)
	{
		if (!current_node) return;

		if (!current_node->get_display()) return;

		current_node->on_render();

		for (GameObj* child : current_node->get_children())
		{
			traverse_exit(child);
		}
	}

	void traverse_render(GameObj* current_node)
	{
		if (!current_node) return;

		if (!current_node->get_display()) return;

		current_node->on_render();

		for (GameObj* child : current_node->get_children())
		{
			traverse_render(child);
		}
	}

	void traverse_update(GameObj* current_node, float delta)
	{
		if (!current_node) return;

		if (!current_node->get_display()) return;

		current_node->on_update(delta);

		for (GameObj* child : current_node->get_children())
		{
			traverse_update(child, delta);
		}
	}

	void traverse_input(GameObj* current_node, const SDL_Event& event)
	{
		if (!current_node) return;

		if (!current_node->get_display()) return;

		current_node->on_input(event);

		for (GameObj* child : current_node->get_children())
		{
			traverse_input(child, event);
		}
	}

	void traverse_delete(GameObj* current_node)
	{
		if (!current_node) return;

		if (current_node->get_parent())
		{
			current_node->get_parent()->get_children().remove(current_node);
		}

		for (GameObj* child : current_node->get_children())
		{
			traverse_render(child);
		}

		delete current_node;
	}

protected:
	// UI ��Ŀ¼
	GameObj* root;
	// UI ��Ŀ¼
	GameObj* background;
	// UI ��Ŀ¼
	GameObj* entity;
	// UI ��Ŀ¼
	GameObj* ui;
	// UI ������ ��ʱ�ò���
	// std::unordered_map<std::string, GameObj* > ui_map;
};

