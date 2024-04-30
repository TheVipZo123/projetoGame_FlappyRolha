#include "Sprite.h"

Sprite::~Sprite()
{
	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);
}

void Sprite::inicializar(GLuint texID, glm::vec3 pos, glm::vec3 escala, float angulo)
{
	this->texID = texID;
	this->pos = pos;
	this->escala = escala;
	this->angulo = angulo;


	vel = 10.0;



	// Aqui setamos as coordenadas x, y e z do tri�ngulo e as armazenamos de forma
	// sequencial, j� visando mandar para o VBO (Vertex Buffer Objects)
	// Cada atributo do v�rtice (coordenada, cores, coordenadas de textura, normal, etc)
	// Pode ser arazenado em um VBO �nico ou em VBOs separados
	GLfloat vertices[] = {
		//x     y    z    r    g    b    s    t
		//Triangulo 0
		-0.5 , 0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0,  //v0
		-0.5 ,-0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,  //v1
		 0.5 , 0.5, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,  //v2
		 //Triangulo 1	
	    -0.5 ,-0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,  //v1
		 0.5 ,-0.5, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,  //v3
		 0.5 , 0.5, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0   //v2
		
	};

	GLuint VBO;
	//Gera��o do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conex�o (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//                                              vertices.data()  
	//Gera��o do identificador do VAO (Vertex Array Object)
	//glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de v�rtices
	// e os ponteiros para os atributos 
//	glBindVertexArray(VAO);
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localiza��o no shader * (a localiza��o dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se est� normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 

	//Atributo 0 - posi��o
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Atributo 1 - cor
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Atributo 2 - coordenadas de textura
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// Observe que isso � permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de v�rtice 
	// atualmente vinculado - para que depois possamos desvincular com seguran�a
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (� uma boa pr�tica desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

}



void Sprite::desenhar()
{
	atualizar();

	glBindTexture(GL_TEXTURE_2D, texID);
	glBindVertexArray(VAO); //Conectando ao buffer de geometria
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindTexture(GL_TEXTURE_2D, 0); //unbind
	glBindVertexArray(0); //unbind


}



void Sprite::moverParaDireita()
{
	pos.x += vel;
	
	
}

void Sprite::moverParaEsquerda()
{
	pos.x -=vel;
	
}

void Sprite::moverEmParabula()
{
	angulo = angulo + 0.5;
	pos.x = pos.x - (vel - 9.8);

	if (pos.x < 10) {
		pos.x = 750;

	}

	float time = 1;
	// Update the position in the vertical direction (parabolic motion)
	// The vertical position (y) changes according to a parabolic trajectory
	// y = initial_position_y + initial_velocity_y * time - 0.5 * gravity * time^2
	// Here, we assume that gravity acts downwards, so it is subtracted
	//pos.y = pos.y + (vel - 9) - (0.5 * 9.8 * time);

	// Update the time variable for each frame
	// You can adjust the time increment as needed
	time = time + 1; // delta_time is the time difference between frames

	// Optionally, you can add a condition to stop the motion at a certain height
	// For example, if you want the object to stop when it reaches the ground level (y = 0)
	if (pos.y <= 0) {
		// Stop the motion or perform any other actions as needed
	}

}

void Sprite::moverEmParabulaDireita()
{
	angulo = angulo - 0.5;
	pos.x = pos.x + (vel - 9.8);


	if (pos.x > 781) {
		pos.x = 0;

	}


}

void Sprite::moverEmParabulaDiagonal()
{
	angulo = angulo - 0.5;
	pos.x = pos.x + (vel - 9.8);

	pos.y = pos.y - (vel - 9.8);


	if (pos.x > 781) {
		pos.x = 50;
		pos.y = 500;

	}


}

void Sprite::moverParaCima()
{
	if (pos.y < 550) {

		pos.y += vel;
	}
	
	


}

void Sprite::moverParaBaixo()
{
	if (pos.y > 10) {
		pos.y -= vel;
	}
	
}

void Sprite::cair()
{
	if (pos.y >= 10.0)
	{
		pos.y -= 0.2;
	}
	else
	{
		pos.x = 10 + rand() % 781;
		pos.y = 1000.0;
	}

	
}

void Sprite::atualizar()
{
	


	glm::mat4 model = glm::mat4(1); //matriz identidade
	model = glm::translate(model, pos);
	model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0, 0.0, 1.0));
	model = glm::scale(model, escala);
	shader->setMat4("model", glm::value_ptr(model));

	
}
