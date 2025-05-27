#include "ResourceManager.h"

struct ImageResInfo
{
	std::string id;
	LPCTSTR path;
};
struct AtlasResInfo
{
	std::string id;
	LPCTSTR path;
	int num = 0;
};

static const std::vector<ImageResInfo> image_info_list =
{
	{ "background", _T(R"(resources\background.png)") },//R标识原始字符串，就无需处理反斜线了
	{ "ui_heart",   _T(R"(resources\ui_heart.png)") },
	
	{ "player_attack_right",    _T(R"(resources\player\attack.png)") },
	{ "player_dead_right",      _T(R"(resources\player\dead.png)") },
	{ "player_fall_right",      _T(R"(resources\player\fall.png)") },
	{ "player_idle_right",      _T(R"(resources\player\idle.png)") },
	{ "player_jump_right",      _T(R"(resources\player\jump.png)") },
	{ "player_run_right",       _T(R"(resources\player\run.png)") },
	{ "player_roll_right",      _T(R"(resources\player\roll.png)") },
	
	{ "player_vfx_attack_down", _T(R"(resources\player\vfx_attack_down.png)") },
	{ "player_vfx_attack_left", _T(R"(resources\player\vfx_attack_left.png)") },
	{ "player_vfx_attack_right",_T(R"(resources\player\vfx_attack_right.png)") },
	{ "player_vfx_attack_up",   _T(R"(resources\player\vfx_attack_up.png)") },
	{ "player_vfx_jump",        _T(R"(resources\player\vfx_jump.png)") },
	{ "player_vfx_land",        _T(R"(resources\player\vfx_land.png)") }
};

static const std::vector<AtlasResInfo> atlas_info_list =
{
	{ "barb_break", _T(R"(resources\enemy\barb_break\%d.png)"), 3 },
	{ "barb_loose", _T(R"(resources\enemy\barb_loose\%d.png)"), 5 },
	{ "silk",       _T(R"(resources\enemy\silk\%d.png)"),       9 },
	{ "sword_left", _T(R"(resources\enemy\sword\%d.png)"),      3 },

	{ "enemy_aim_left",               _T(R"(resources\enemy\aim\%d.png)"),                9 },
	{ "enemy_dash_in_air_left",       _T(R"(resources\enemy\dash_in_air\%d.png)"),        2 },
	{ "enemy_dash_on_floor_left",     _T(R"(resources\enemy\dash_on_floor\%d.png)"),      2 },
	{ "enemy_fall_left",              _T(R"(resources\enemy\fall\%d.png)"),               4 },
	{ "enemy_idle_left",              _T(R"(resources\enemy\idle\%d.png)"),               6 },
	{ "enemy_jump_left",              _T(R"(resources\enemy\jump\%d.png)"),               8 },
	{ "enemy_run_left",               _T(R"(resources\enemy\run\%d.png)"),                8 },
	{ "enemy_squat_left",             _T(R"(resources\enemy\squat\%d.png)"),              10 },
	{ "enemy_throw_barb_left",        _T(R"(resources\enemy\throw_barb\%d.png)"),         8 },
	{ "enemy_throw_silk_left",        _T(R"(resources\enemy\throw_silk\%d.png)"),         17 },
	{ "enemy_throw_sword_left",       _T(R"(resources\enemy\throw_sword\%d.png)"),        16 },

	{ "enemy_vfx_dash_in_air_left",   _T(R"(resources\enemy\vfx_dash_in_air\%d.png)"),    5 },
	{ "enemy_vfx_dash_on_floor_left", _T(R"(resources\enemy\vfx_dash_on_floor\%d.png)"),  6 },
};



static inline bool check_image_valid(IMAGE* img)
{
	return GetImageBuffer(img);
}

ResourceManager* ResourceManager::manager = nullptr;

void ResourceManager::load()
{
	for (const auto& info: image_info_list)
	{
		IMAGE* p = new IMAGE();
		loadimage(p, info.path);
		if (!check_image_valid(p))
		{
			throw info.path;
		}
		image_pool[info.id] = p;
	}

	for (const auto& info: atlas_info_list)
	{
		Atlas* p = new Atlas();
		p->load(info.path, info.num);
		for (int i = 0; i < p->get_size(); i++)
		{
			IMAGE* img = p->getImage(i);
			if (!check_image_valid(img))
			{
				throw info.path;
			}
		}
		atlas_pool[info.id] = p;
	}

	hor_flip_img("player_attack_right", "player_attack_right", 5);
	hor_flip_img("player_dead_right", "player_dead_right", 6);
	hor_flip_img("player_fall_right", "player_fall_right", 5);
	hor_flip_img("player_idle_right", "player_idle_right", 5);
	hor_flip_img("player_jump_right", "player_jump_right", 5);
	hor_flip_img("player_run_right", "player_run_right", 10);
	hor_flip_img("player_roll_right", "player_roll_right", 7);

	hor_flip_atlas("enemy_aim_left", "enemy_aim_right");
	hor_flip_atlas("enemy_dash_in_air_left", "enemy_dash_in_air_right");
	hor_flip_atlas("enemy_dash_on_floor_left", "enemy_dash_on_floor_right");
	hor_flip_atlas("enemy_fall_left", "enemy_fall_right");
	hor_flip_atlas("enemy_idle_left", "enemy_idle_right");
	hor_flip_atlas("enemy_jump_left", "enemy_jump_right");
	hor_flip_atlas("enemy_run_left", "enemy_run_right");
	hor_flip_atlas("enemy_squat_left", "enemy_squat_right" );
	hor_flip_atlas("enemy_throw_barb_left", "enemy_throw_barb_right");
	hor_flip_atlas("enemy_throw_silk_left", "enemy_throw_silk_right");
	hor_flip_atlas("enemy_throw_sword_left", "enemy_throw_sword_right");

	hor_flip_atlas("enemy_vfx_dash_in_air_left", "enemy_vfx_dash_in_air_right");
	hor_flip_atlas("enemy_vfx_dash_on_floor_left", "enemy_vfx_dash_on_floor_right");
}

ResourceManager* ResourceManager::instance()
{
	if (nullptr == manager)
	{
		manager = new ResourceManager();
	}
	return manager;
}

Atlas* ResourceManager::find_atlas(const std::string& id)const
{
}

IMAGE* ResourceManager::find_image(const std::string& id)const
{
	image_pool[id]
}

void ResourceManager::hor_flip_img(IMAGE* src, IMAGE* dst, int num = 1)
{
	int w = src->getwidth();
	int h = src->getheight();
	dst->Resize(w, h);
	DWORD* src_buf = GetImageBuffer(src);
	DWORD* dst_buf = GetImageBuffer(dst);
	for (int i = 0; i < w * h; ++i)
	{
		dst_buf[i] = src_buf[i / w * w + (w - i % w) - 1];
	}
}

void ResourceManager::hor_flip_img(const std::string& src, const std::string& dst, int num = 1)
{
}

void ResourceManager::hor_flip_atlas(const std::string& src, const std::string& dst)
{
}


ResourceManager::ResourceManager() = default;
ResourceManager::~ResourceManager() = default;
