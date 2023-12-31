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
	shared_ptr<Collider> _ground2;

	vector<shared_ptr<Creature>> _creatures;

	vector<shared_ptr<Tile>> _tiles;
};