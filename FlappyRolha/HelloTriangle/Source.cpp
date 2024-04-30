/* Hello Triangle - c�digo adaptado de https://learnopengl.com/#!Getting-started/Hello-Triangle 
 *
 * Adaptado por Rossana Baptista Queiroz
 * para a disciplina de Processamento Gr�fico - Unisinos
 * Vers�o inicial: 7/4/2017
 * �ltima atualiza��o em 14/08/2023
 *
 */

#include <iostream>
#include <string>
#include <assert.h>

//STB IMAGE
#include<stb_image.h>


using namespace std;
//using namespace glm; //para n�o usar glm::

//Classe para manipula��o dos shaders
#include "Shader.h"

//Classe para manipula��o das sprites
#include "Sprite.h"
#include <vector>

// Prot�tipo da fun��o de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Prot�tipos das fun��es
GLuint loadTexture(string texturePath);

// Dimens�es da janela (pode ser alterado em tempo de execu��o)
const GLuint WIDTH = 800, HEIGHT = 600;

bool CheckCollision(Sprite& one, Sprite& two);

//Variaveis globais
Sprite spr;

 int garrafasDesviadas;

int numFrames = 5;
float frameWidth = 2.0;

int currentFrame = 1;


// Fun��o MAIN
int main()
{
	

	// Inicializa��o da GLFW
	glfwInit();

	// Inicializa��o da semente para gera��o de nros aleat�rios
	srand((int)glfwGetTime());

	//Muita aten��o aqui: alguns ambientes n�o aceitam essas configura��es
	//Voc� deve adaptar para a vers�o do OpenGL suportada por sua placa
	//Sugest�o: comente essas linhas de c�digo para desobrir a vers�o e
	//depois atualize (por exemplo: 4.5 com 4 e 5)
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

	//Essencial para computadores da Apple
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif

	// Cria��o da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Flappy Rolha! -- A Fuga das Garrafas!", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da fun��o de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	

	// GLAD: carrega todos os ponteiros d fun��es da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;

	}

	// Obtendo as informa��es de vers�o
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;
	
	//Habilitar teste de profundidade
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS); //a cada ciclo

	//Habilitar o modo de transpar�ncia (blend - mistura de cores)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	vector<GLuint> texIDs;
	// Compilando e buildando o programa de shader
	//Shader shader("../shaders/helloTriangle.vs", "../shaders/helloTriangle.fs");
	Shader shader("../shaders/tex.vs", "../shaders/tex.fs");

	GLuint texID = loadTexture("../../Textures/pixelWall.png");
	GLuint texID2 = loadTexture("../../Textures/characters/PNG/Barrel.png");
	GLuint texID3 = loadTexture("../../Textures/backgrounds/PNG/city_8/7.png");
	GLuint texID4 = loadTexture("../../Textures/characters/PNG/Icon46.png");
	GLuint texID5 = loadTexture("../../Textures/characters/PNG/Homeless_1/idle1Left.png");
	GLuint texID6 = loadTexture("../../Textures/characters/PNG/Homeless_1/drinkingLeft.png");
	GLuint texID7 = loadTexture("../../Textures/characters/PNG/Homeless_1/AttackCopyLeft.png");
	GLuint texID8 = loadTexture("../../Textures/craftpix-net-159039-free-pirate-stuff-pixel-art-icons/PNG/Transperent/Icon48.png");
	GLuint texID9 = loadTexture("../../Textures/characters/PNG/Homeless_1/idle1.png");
	GLuint texID10 = loadTexture("../../Textures/characters/PNG/Homeless_1/drinking.png");
	GLuint texID11 = loadTexture("../../Textures/characters/PNG/Homeless_1/AttackCopy.png");
	GLuint texID12 = loadTexture("../../Textures/characters/PNG/Fish-rod.png");
	//GLuint texID8 = loadTexture("../../Textures/characters/PNG/Homeless_1/idle1.png");

	//texIDs.push_back(loadTexture("../../Textures/characters/PNG/Homeless_1/idle1Left.png"));
	//texIDs.push_back(loadTexture("../../Textures/characters/PNG/Homeless_1/idle1.png"));
	//texIDs.push_back(loadTexture("../../Textures/characters/PNG/Homeless_1/idle1.png"));
	//texIDs.push_back(loadTexture("../../Textures/characters/PNG/Homeless_1/idle1.png"));
	//Cria��o de uma sprite





	spr.setShader(&shader);
	spr.inicializar(texID2, glm::vec3(400.0, 150.0, 0.0), glm::vec3(24.0, 24.0, 1.0));

	//Sprite spr1;
	//spr1.setShader(&shader);
	//spr1.inicializar(texID2, glm::vec3(400.0, 150.0, 0.0), glm::vec3(24.0, 24.0, 1.0));
	
	Sprite background;
	background.setShader(&shader);
	background.inicializar(texID3, glm::vec3(400.0, 300.0, 0.0), glm::vec3(1920.0/2.0, 1200.0/2.0, 1.0));

	Sprite garrafa;
	garrafa.setShader(&shader);
	garrafa.inicializar(texID4, glm::vec3(400.0, 900.0, 0.0), glm::vec3(42.0, 42.0, 1.0));




	


	//LEFT BOTTOM

	Sprite bebado;
	bebado.setShader(&shader);
	bebado.inicializar(texID5, glm::vec3(750.0, 200.0, 0.0), glm::vec3(100.0, 150.0, 1.0));

	Sprite bebado1;
	bebado1.setShader(&shader);
	bebado1.inicializar(texID6, glm::vec3(750.0, 200.0, 0.0), glm::vec3(110.0, 160.0, 1.0));

	Sprite bebado2;
	bebado2.setShader(&shader);
	bebado2.inicializar(texID7, glm::vec3(750.0, 200.0, 0.0), glm::vec3(120.0, 170.0, 1.0));

	Sprite garrafa1;
	garrafa1.setShader(&shader);
	garrafa1.inicializar(texID8, glm::vec3(750.0, 200.0, 0.0), glm::vec3(42.0, 42.0, 1.0));


	//LEFT TOP

	Sprite bebadoLeftTop;
	bebadoLeftTop.setShader(&shader);
	bebadoLeftTop.inicializar(texID5, glm::vec3(750.0, 400.0, 0.0), glm::vec3(100.0, 150.0, 1.0));

	Sprite bebadoLeftTop1;
	bebadoLeftTop1.setShader(&shader);
	bebadoLeftTop1.inicializar(texID6, glm::vec3(750.0, 400.0, 0.0), glm::vec3(110.0, 160.0, 1.0));

	Sprite bebadoLeftTop2;
	bebadoLeftTop2.setShader(&shader);
	bebadoLeftTop2.inicializar(texID7, glm::vec3(750.0, 400.0, 0.0), glm::vec3(120.0, 170.0, 1.0));

	Sprite garrafaLeftTop;
	garrafaLeftTop.setShader(&shader);
	garrafaLeftTop.inicializar(texID8, glm::vec3(750.0, 400.0, 0.0), glm::vec3(42.0, 42.0, 1.0));

	//RIGHT TOP

	Sprite bebado3;
	bebado3.setShader(&shader);
	bebado3.inicializar(texID9, glm::vec3(50.0, 300.0, 0.0), glm::vec3(100.0, 150.0, 1.0));

	Sprite bebado4;
	bebado4.setShader(&shader);
	bebado4.inicializar(texID10, glm::vec3(50.0, 300.0, 0.0), glm::vec3(110.0, 160.0, 1.0));

	Sprite bebado5;
	bebado5.setShader(&shader);
	bebado5.inicializar(texID11, glm::vec3(50.0, 300.0, 0.0), glm::vec3(120.0, 170.0, 1.0));

	Sprite garrafa2;
	garrafa2.setShader(&shader);
	garrafa2.inicializar(texID8, glm::vec3(50.0, 300.0, 0.0), glm::vec3(42.0, 42.0, 1.0));

	//RIGHT BOTTOM

	Sprite bebadoRightBottom;
	bebadoRightBottom.setShader(&shader);
	bebadoRightBottom.inicializar(texID9, glm::vec3(50.0, 100.0, 0.0), glm::vec3(100.0, 150.0, 1.0));

	Sprite bebadoRightBottom1;
	bebadoRightBottom1.setShader(&shader);
	bebadoRightBottom1.inicializar(texID10, glm::vec3(50.0, 100.0, 0.0), glm::vec3(110.0, 160.0, 1.0));

	Sprite bebadoRightBottom2;
	bebadoRightBottom2.setShader(&shader);
	bebadoRightBottom2.inicializar(texID11, glm::vec3(50.0, 100.0, 0.0), glm::vec3(120.0, 170.0, 1.0));

	Sprite garrafaRightBottom;
	garrafaRightBottom.setShader(&shader);
	garrafaRightBottom.inicializar(texID8, glm::vec3(50.0, 100.0, 0.0), glm::vec3(42.0, 42.0, 1.0));

	//Diagonal

	Sprite bebadoRightDiagonal;
	bebadoRightDiagonal.setShader(&shader);
	bebadoRightDiagonal.inicializar(texID9, glm::vec3(50.0, 500.0, 0.0), glm::vec3(100.0, 150.0, 1.0));

	Sprite bebadoRightDiagonal1;
	bebadoRightDiagonal1.setShader(&shader);
	bebadoRightDiagonal1.inicializar(texID10, glm::vec3(50.0, 500.0, 0.0), glm::vec3(110.0, 160.0, 1.0));

	Sprite bebadoRightDiagonal2;
	bebadoRightDiagonal2.setShader(&shader);
	bebadoRightDiagonal2.inicializar(texID11, glm::vec3(50.0, 500.0, 0.0), glm::vec3(120.0, 170.0, 1.0));

	Sprite garrafaRightDiagonal;
	garrafaRightDiagonal.setShader(&shader);
	garrafaRightDiagonal.inicializar(texID8, glm::vec3(50.0, 500.0, 0.0), glm::vec3(42.0, 42.0, 1.0));


	//Premio

	Sprite premio;
	premio.setShader(&shader);
	premio.inicializar(texID12, glm::vec3(450.0, 250.0, 0.0), glm::vec3(42.0, 42.0, 1.0));

	//Ativando o buffer de textura 0 da opengl
	glActiveTexture(GL_TEXTURE0);

	shader.Use();

	//Matriz de proje��o paralela ortogr�fica
    glm::mat4 projection = glm::ortho(0.0,800.0,0.0,600.0,-1.0,1.0);
	//Enviando para o shader a matriz como uma var uniform
	shader.setMat4("projection", glm::value_ptr(projection));
	
	//Matriz de transforma��o do objeto (matriz de modelo)
	shader.setInt("texBuffer", 0);
	
	// Loop da aplica��o - "game loop"
	double lastFrameTime = glfwGetTime();  // Initialize the timer
	double deltaTime;  // Variable to store the time difference between frames
	
	// Loop da aplica��o - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as fun��es de callback correspondentes
		glfwPollEvents();

		// Calculate delta time
		double currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		// Definindo as dimens�es da viewport com as mesmas dimens�es da janela da aplica��o
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height); //unidades de tela: pixel
		
		// Limpa o buffer de cor
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT);

		background.desenhar();
		
		spr.desenhar();
		//spr1.desenhar();
		//spr1.cair();

		if (currentFrameTime > 10) {
			
			bebado.desenhar();
			if (currentFrameTime > 14) {

				bebado.moverParaDireita();
				bebado1.desenhar();
				
				if (currentFrameTime > 18) {

					bebado1.moverParaDireita();
					bebado2.desenhar();

				
						garrafa1.moverEmParabula();
						garrafa1.desenhar();


						

					
				
				}
			}

			

		}

		if (currentFrameTime > 30) {

			bebado3.desenhar();
			if (currentFrameTime > 34) {

				bebado3.moverParaEsquerda();
				bebado4.desenhar();

				if (currentFrameTime > 38) {

					bebado4.moverParaEsquerda();
					bebado5.desenhar();


					garrafa2.moverEmParabulaDireita();
					garrafa2.desenhar();



				}
			}

		}

		if (currentFrameTime > 43) {

			bebadoLeftTop.desenhar();
			if (currentFrameTime > 46) {

				bebadoLeftTop.moverParaDireita();
				bebadoLeftTop1.desenhar();

				if (currentFrameTime > 49) {

					bebadoLeftTop1.moverParaDireita();
					bebadoLeftTop2.desenhar();


					garrafaLeftTop.moverEmParabula();
					garrafaLeftTop.desenhar();



				}
			}

		}

		if (currentFrameTime > 55) {

			bebadoRightBottom.desenhar();
			if (currentFrameTime > 60) {

				bebadoRightBottom.moverParaEsquerda();
				bebadoRightBottom1.desenhar();

				if (currentFrameTime > 65) {

					bebadoRightBottom1.moverParaEsquerda();
					bebadoRightBottom2.desenhar();


					garrafaRightBottom.moverEmParabulaDireita();
					garrafaRightBottom.desenhar();



				}
			}

		}

		if (currentFrameTime > 70) {

			bebadoRightDiagonal.desenhar();
			if (currentFrameTime > 75) {

				bebadoRightDiagonal.moverParaEsquerda();
				bebadoRightDiagonal1.desenhar();

				if (currentFrameTime > 80) {

					bebadoRightDiagonal1.moverParaEsquerda();
					bebadoRightDiagonal2.desenhar();


					garrafaRightDiagonal.moverEmParabulaDiagonal();
					garrafaRightDiagonal.desenhar();



				}
			}

		}



		if (currentFrameTime > 90) {

			premio.desenhar();

			if (CheckCollision(premio, spr)) {


				cout << "Ganhou!!" << endl;

				glfwSetWindowShouldClose(window, GL_TRUE);
					
				
			}
		
		}

		
		if (CheckCollision(garrafaRightDiagonal , spr)) {

			cout << "Perdeu!!" << endl;

			glfwSetWindowShouldClose(window, GL_TRUE);


		}


		if (CheckCollision(garrafaRightBottom, spr)) {

			cout << "Perdeu!!" << endl;

			glfwSetWindowShouldClose(window, GL_TRUE);

			
		}

		if (CheckCollision(garrafaLeftTop, spr)) {


			cout << "Perdeu!!" << endl;

			glfwSetWindowShouldClose(window, GL_TRUE);

			
		}

		if (CheckCollision(garrafa1, spr)) {


			cout << "Perdeu!!" << endl;

			glfwSetWindowShouldClose(window, GL_TRUE);

		
		}

		if (CheckCollision(garrafa2, spr)) {


			cout << "Perdeu!!" << endl;

			glfwSetWindowShouldClose(window, GL_TRUE);


		}
	

		garrafa.cair();
		garrafa.desenhar();

		if (CheckCollision(garrafa, spr)) {

			cout << "Perdeu!!" << endl;

			glfwSetWindowShouldClose(window, GL_TRUE);
	
	}


		
		// Troca os buffers da tela
		glfwSwapBuffers(window);

		
	}
	
	// Finaliza a execu��o da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

// Fun��o de callback de teclado - s� pode ter uma inst�ncia (deve ser est�tica se
// estiver dentro de uma classe) - � chamada sempre que uma tecla for pressionada
// ou solta via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_UP )
	{

		spr.moverParaCima();
		
	}

	if (key == GLFW_KEY_DOWN)
	{

		spr.moverParaBaixo();

	}

	
	if ( key == GLFW_KEY_RIGHT)
	{
		spr.moverParaDireita();
		
	}
	if ( key == GLFW_KEY_LEFT)
	{
		spr.moverParaEsquerda();
	
	}
	
}

bool CheckCollision(Sprite& one, Sprite& two)
{
	// collision x-axis?
	bool collisionX = one.getXMax() >= two.getXMin() &&
		two.getXMax() >= one.getXMin();
	// collision y-axis?
	bool collisionY = one.getYMax() >= two.getYMin() &&
		two.getYMax() >= one.getYMin();
	// collision only if on both axes
	return collisionX && collisionY;
}

GLuint loadTexture(string texturePath)
{
	GLuint texID;

	// Gera o identificador da textura na mem�ria 
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	//Configura��o do par�metro WRAPPING nas coords s e t
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Confiruga��o do par�metro FILTERING na minifica��o e magnifica��o da textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3) //jpg, bmp
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else //png
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}

