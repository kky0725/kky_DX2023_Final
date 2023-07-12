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

private:
	shared_ptr<Player> _player;
	//to do : ���� �߰�
	shared_ptr<Collider> _ground;
};