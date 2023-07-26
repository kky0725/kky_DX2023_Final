#pragma once
class Player;

class TestScene : public Scene
{
public:
	TestScene();
	virtual ~TestScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void CheckAttack();

private:
	shared_ptr<Player> _player;
	shared_ptr<Collider> _ground;

	vector<shared_ptr<Creature>> _creatures;
};