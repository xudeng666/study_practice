#pragma once
#include "game_obj.h"

class GameImg : public GameObj
{
public:
	GameImg() = default;
	~GameImg() = default;
	GameImg(const Vector2 pos);
	GameImg(const Vector2 pos, const std::string name);

	void on_update(float delta) override;
	void on_render(const Camera* camera) override;

protected:
	SDL_Texture* texture = nullptr;
};

