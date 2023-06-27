#pragma once
class Player;

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<Player> _player;
};