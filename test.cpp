#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace::std;
using namespace::glm;

int main() {

	vec4 vec(1.0f, 0, 0, 1.0f);
	
	mat4 trans;
	trans = translate(trans, vec3(2.0f, 0, -1.0f));
	vec = trans * vec;

	cout << vec.x << " " << vec.y << " " << vec.z << endl;
	while(1) {}
	return 0;
}