/**
	ParticleEmitter.h

	Purpose: ParticleEmitter.h is the header file for the ParticleEmitter class.
			The Particle Emitter class allows the creation of particle effects
			in the scene. 

	@author Nathan Nette
*/
#pragma once
#include "soxCore.h"

/**
	The Particle Emitter class is used to create a particle system.
		the particles emit from where you create this object.
*/
class ParticleEmitter
{
public:
	/**
		The Particle Emitter constructor assigns the values to 0
			as default.
	*/
	ParticleEmitter();

	/**
		The Particle Emitter deconstructor deletes anything that
			needs to be cleaned up on termination of the program.
	*/
	virtual ~ParticleEmitter();


	//---------Particle-------
	struct Particle
	{
		glm::vec3 position;
		glm::vec3 velocity;
		glm::vec4 colour;
		float size;
		float lifetime;
		float lifespan;
	};

	//----Particle Vertex----
	struct ParticleVertex
	{
		glm::vec4 position;
		glm::vec4 colour;
	};

	/**
		initialise creates a new particle effect based on the 
			params for this function.

			@param1 a_maxParticles is the maximum amount of particles
				that can exist at once.

			@param2  a_emitRate is the speed that particles emit at.

			@param3 a_lifetimeMin is the minimum life time of a particle.

			@param4 a_lifetimeMax is the maximum life time of a particle.

			@param5 a_velocityMin is the minimum of how fast the particles move.

			@param6 a_velocityMax is the maximum of how fast the particles move.

			@param7 a_startSize is the size of the particles when they first emit.

			@param8 a_endSize is the size of the particles when they end.

			@param9 a_startColour is the colour of the particle when they spawn.

			@param10 a_endColour is the colour of the particle when they end.
	*/
	void initialise(unsigned int a_maxParticles, 
		unsigned int a_emitRate,
		float a_lifetimeMin, float a_lifetimeMax,
		float a_velocityMin, float a_velocityMax,
		float a_startSize, float a_endSize,
		const glm::vec4& a_startColour, const glm::vec4& a_endColour);

	/**
		emit is the function to be called to spawn a new particle.
			it only runs if there is currently less than the maximum
			amount. This means that when one dies, a new one spawn 
			straight away.
	*/
	void emit();

	/**
		update is called every frame. It does all of the necessary 
			math to move every particle and change their colour.
			Also checks to see how many exist. If there are less
			than the maximum, call emit.
	*/
	void update(float a_deltaTime, const glm::mat4& a_cameraTransform);

	/**
		draw is the function that actually draws them to the screen.
	*/
	void draw();

protected:



	Particle * m_particles;
	unsigned int m_firstDead;
	unsigned int m_maxParticles;
	unsigned int m_vao, m_vbo, m_ibo;
	ParticleVertex* m_vertexData;

	glm::vec3 m_position;
	float m_emitTimer;
	float m_emitRate;
	float m_lifespanMin;
	float m_lifespanMax;
	float m_velocityMin;
	float m_velocityMax;
	float m_startSize;
	float m_endSize;
	glm::vec4 m_startColour;
	glm::vec4 m_endColour;


};

