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
		draw is the function that actually renders them to the screen.
	*/
	void draw();

protected:
	// A particle pointer. These will be created in an array to form
	//	the particles.
	Particle * m_particles;

	// An int to store the first dead particle.
	unsigned int m_firstDead;

	// An int to store the maximum amount of particles that can be spawned.
	unsigned int m_maxParticles;

	// 3 ints to store the vao, vbo and ibo.
	unsigned int m_vao, m_vbo, m_ibo;

	// A pointer to particle vertex data.
	ParticleVertex* m_vertexData;

	// A vec3 that stores the position of the emitter.
	glm::vec3 m_position;

	// A float to store how long the emitter has been going for.
	float m_emitTimer;
	
	// The rate of which it emits particles.
	float m_emitRate;

	// The minimum life span of a particle.
	float m_lifespanMin;

	// The maximum life span of a particle.
	float m_lifespanMax;

	// The slowest the velocity can be for a particle.
	float m_velocityMin;

	// The fastest the velocity can be for a particle.
	float m_velocityMax;

	// The size of a particle when it is first created.
	float m_startSize;

	// The size of a particle when it reaches its end.
	float m_endSize;

	// The colour of a particle when it is first created.
	glm::vec4 m_startColour;

	// The colour of a particle when it reaches the end.
	glm::vec4 m_endColour;


};

