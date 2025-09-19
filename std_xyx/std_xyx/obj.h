#pragma once

#include <SDL.h>
#include <string>

#define DEFINE_TYPE_NAME(ClassName) \
    static const std::string type_name; \
    const std::string& get_type_name() const override { return type_name; }

#define INIT_TYPE_NAME(ClassName) \
    const std::string ClassName::type_name = #ClassName;

class Obj
{
public:
	Obj() = default;
    virtual ~Obj() = default;

    virtual void on_init() = 0;
    virtual void on_enter() = 0;
    virtual void on_exit() = 0;
    virtual void on_input(const SDL_Event& event) = 0;
    virtual void on_update(float delta) = 0;
    virtual void on_render() = 0;

    virtual const std::string& get_type_name() const = 0;

    template <typename T> bool is_type()const
    {
        return get_type_name == T::type::name;
    }

    /*…Ë÷√ID*/
    virtual void set_ID(const std::string str) = 0;
    virtual void set_ID(const std::string str, const int num) = 0;
    /*ªÒ»°ID*/
    virtual std::string get_ID() = 0;
protected:
    std::string ID;
};
