#pragma once

#include "obj.h"

/*场景类-基类*/
class Scene:public Obj
{
public:
	Scene() = default;
	Scene(const std::string id);
	Scene(const std::string id, const int num);
	virtual ~Scene() = default;

	DEFINE_TYPE_NAME(Scene);

	virtual void on_init() override;
	virtual void on_enter() override;
	virtual void on_exit() override;
	virtual void on_input(const SDL_Event& event) override;
	virtual void on_update(float delta) override;
	virtual void on_render() override;
	virtual void set_ID(const std::string& str) override;
	virtual void set_ID(const std::string& str, const int num) override;
	virtual std::string get_ID() override;
};

INIT_TYPE_NAME(Scene);