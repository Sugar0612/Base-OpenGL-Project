#include "Material.h"

Material::Material(Shader *& _myShader, vec3 _anbiemt, unsigned int &_diffuse, vec3 _specular, float _shininess) :
	myShader(_myShader), anbiemt(_anbiemt), diffuse(_diffuse), specular(_specular), shininess(_shininess)
{
		
}

