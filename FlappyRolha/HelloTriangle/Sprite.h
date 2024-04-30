#pragma once

#include "Shader.h"

class Sprite
{
public:
	Sprite() {}
	~Sprite();
	void inicializar(GLuint texID,glm::vec3 pos = glm::vec3(0.0,0.0,0.0), glm::vec3 escala = glm::vec3(1.0,1.0,1.0),float angulo = 0.0);
	void desenhar();
	void moverEmParabula();
	void moverEmParabulaDireita();
	void moverEmParabulaDiagonal();
	void moverParaDireita();
	void moverParaEsquerda();
	void moverParaCima();
	void moverParaBaixo();
	



	void cair();

	inline void setShader(Shader* shader) { this->shader = shader; }


	inline float getXMin() const { return pos.x - 0.5f * (escala.x - 5 ); }
	inline float getXMax() const { return pos.x + 0.5f * (escala.x - 5 ); }
	inline float getYMin() const { return pos.y - 0.5f * (escala.y  - 2); }
	inline float getYMax() const { return pos.y + 0.5f * (escala.y - 2); }
	
protected:
	void atualizar();
	GLuint VAO; //identificador do buffer de geometria, indicando os atributos dos vértices
	GLuint texID; //identificador do buffer de textura

	//Variáveis com as infos para aplicar as transformações no objeto
	glm::vec3 pos, escala;
	float angulo;

	//Uma referência ao programa de shader que a sprite irá usar para seu desenho
	Shader *shader;

	//Atributos para controle das ações
	float vel;

};

