#include "texture.h"



Texture::Texture()
{
	flipVertical = true;
}

Texture::Texture(string path)
{
	stbi_set_flip_vertically_on_load(flipVertical);
	data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (!data)
	{
		throw runtime_error("Failed to load texture.");
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

}


Texture::~Texture()
{
	stbi_image_free(data);
}
