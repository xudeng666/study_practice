#pragma once
#include "phf_obj.h"

/*≤Õ∆∑∂—ª˘¿‡*/
class PhfBundle :
    public PhfObj, public PhfMeal
{
public:
    PhfBundle() = default;
    virtual ~PhfBundle() = default;

    PhfBundle(const std::string& id) : PhfObj(id) {}
    PhfBundle(const std::string& id, int num) : PhfObj(id, num) {}

    DEFINE_TYPE_NAME(PhfBundle);

    virtual void on_init() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_cursor_down() override;
    virtual void on_cursor_up() override;
//
//protected:
//    Meal get_meal();
//    void set_meal(Meal m);
//    Meal get_picked_meal();
//    void set_picked_meal(Meal m);
//    void change_picked_meal(Meal m);
//
//protected:
//    Meal meal = Meal::None;			// ◊‘…Ì¿‡–Õ
//    Meal picked_meal = Meal::None;	// µ±«∞ƒ√»°¿‡–Õ
};


/*ø…¿÷∂—*/
class ColaBundle :
    public PhfBundle
{
public:
    ColaBundle() = default;
    virtual ~ColaBundle() = default;

    ColaBundle(const std::string& id) : PhfBundle(id) {}
    ColaBundle(const std::string& id, int num) : PhfBundle(id, num) {}

    DEFINE_TYPE_NAME(ColaBundle);

    virtual void on_init() override;
};

/*¿◊±Ã∂—*/
class SpriteBundle :
    public PhfBundle
{
public:
    SpriteBundle() = default;
    virtual ~SpriteBundle() = default;

    SpriteBundle(const std::string& id) : PhfBundle(id) {}
    SpriteBundle(const std::string& id, int num) : PhfBundle(id, num) {}

    DEFINE_TYPE_NAME(SpriteBundle);

    virtual void on_init() override;
};

/*≤Õ∫–∂—*/
class TbBundle :
    public PhfBundle
{
public:
    TbBundle() = default;
    virtual ~TbBundle() = default;

    TbBundle(const std::string& id) : PhfBundle(id) {}
    TbBundle(const std::string& id, int num) : PhfBundle(id, num) {}

    DEFINE_TYPE_NAME(TbBundle);

    virtual void on_init() override;
};

/*»‚ÕË∂—*/
class MbBoxBundle :
    public PhfBundle
{
public:
    MbBoxBundle() = default;
    virtual ~MbBoxBundle() = default;

    MbBoxBundle(const std::string& id) : PhfBundle(id) {}
    MbBoxBundle(const std::string& id, int num) : PhfBundle(id, num) {}

    DEFINE_TYPE_NAME(MbBoxBundle);

    virtual void on_init() override;
};

/*ª∆ÏÀº¶∂—*/
class BcBoxBundle :
    public PhfBundle
{
public:
    BcBoxBundle() = default;
    virtual ~BcBoxBundle() = default;

    BcBoxBundle(const std::string& id) : PhfBundle(id) {}
    BcBoxBundle(const std::string& id, int num) : PhfBundle(id, num) {}

    DEFINE_TYPE_NAME(BcBoxBundle);

    virtual void on_init() override;
};

/*∫Ï…’»‚∂—*/
class RcpBoxBundle :
    public PhfBundle
{
public:
    RcpBoxBundle() = default;
    virtual ~RcpBoxBundle() = default;

    RcpBoxBundle(const std::string& id) : PhfBundle(id) {}
    RcpBoxBundle(const std::string& id, int num) : PhfBundle(id, num) {}

    DEFINE_TYPE_NAME(RcpBoxBundle);

    virtual void on_init() override;
};
