#ifndef ChequeredBoard_h
#define ChequeredBoard_h

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Object3d.hpp"

class ChequeredBoard : public Object3d, public sf::Drawable
{
private:
	Vector3d<int> numberOfCells;
	Vector3d<float> sizeOfCell;
	sf::Texture texture1;
	sf::Texture texture2;

	void drawCells(bool flag, const sf::Texture& texture) const
	{
		auto position = getPosition();
		sf::Texture::bind(&texture);
		glBegin(GL_QUADS);
		for (int i = 0; i < numberOfCells.x; i++)
		{
			for (int j = 0; j < numberOfCells.y; j++)
			{
				if ((i + j) % 2 == flag)
				{
					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(position.x + i * sizeOfCell.x + 0.0f, 0.0f,
						position.y + j * sizeOfCell.y + 0.0f);
					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(position.x + i * sizeOfCell.x + 1.0f, 0.0f,
						position.y + j * sizeOfCell.y + 0.0f);
					glTexCoord2f(1.0f, 1.0f);
					glVertex3f(position.x + i * sizeOfCell.x + 1.0f, 0.0f,
						position.y + j * sizeOfCell.y + 1.0f);
					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(position.x + i * sizeOfCell.x + 0.0f, 0.0f,
						position.y + j * sizeOfCell.y + 1.0f);
				}
			}
		}
		glEnd();
		sf::Texture::bind(nullptr);
	}
public:
	explicit ChequeredBoard(const Vector3d<int>& numberOfCells,
		const Vector3d<float>& sizeOfCell,
		const Vector3d<float>& position,
		const sf::Texture& texture1,
		const sf::Texture& texture2) :
		numberOfCells(numberOfCells), sizeOfCell(sizeOfCell),
		Object3d(position),
		texture1(texture1), texture2(texture2) {}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		drawCells(true, texture1);
		drawCells(false, texture2);

	}
};

#endif