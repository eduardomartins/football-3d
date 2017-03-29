package main;

import org.lwjgl.glfw.GLFW;

import org.lwjgl.glfw.GLFWVidMode;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		if(!GLFW.glfwInit()){ 
			throw new IllegalStateException("O sistama falhou ao iniciar GLFW");
		}
		
		GLFW.glfwWindowHint(GLFW.GLFW_VISIBLE, GLFW.GLFW_FALSE);
		long window = GLFW.glfwCreateWindow(800, 600, "Jogo - Computação Gráfica", 0, 0);
		
		if(window == 0){
			throw new IllegalStateException("Falha ao criar a janela");
		}
		
		GLFWVidMode vidMode = GLFW.glfwGetVideoMode(GLFW.glfwGetPrimaryMonitor());
		
		GLFW.glfwSetWindowPos(window, vidMode.width()/2, vidMode.height()/2);
		
		GLFW.glfwShowWindow(window);
		
		while(!GLFW.glfwWindowShouldClose(window)){
			GLFW.glfwPollEvents();
		}
		GLFW.glfwTerminate();
	}

}
