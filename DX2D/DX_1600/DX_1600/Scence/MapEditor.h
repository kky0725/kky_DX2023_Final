#pragma once
class MapEditor : public Scene
{
public:
	MapEditor();
	~MapEditor();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Init();
	virtual void End();

	void Create();


private:
	string _label = "";

};