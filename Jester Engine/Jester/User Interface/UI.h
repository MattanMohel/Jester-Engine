
#include <string>
#include <vector>

class Gameobject;
class Component;
class Vector2;

namespace Jester::UI
{
	void RenderHierarchy();
	void RenderVector2(const std::string&, Vector2&, float); 

	//template<typename T>
	//void RenderVector(const std::string&, std::vector<T>);

	//make into template?
	void RenderFloat(const std::string&, float&, bool);
	void RenderBool(const std::string&, bool&, bool);
	void RenderInt(const std::string&, int&, bool);

	void RenderGameobject(Gameobject*); 
	void RenderComponent(Component*);
}