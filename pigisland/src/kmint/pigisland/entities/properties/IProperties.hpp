#pragma once

#include "kmint/play.hpp"

namespace kmint {
	namespace pigisland {
		class IProperties {
		public:
			virtual double wanderJitter() const = 0;
			virtual double wanderRadius() const = 0;
			virtual double wanderDistance() const = 0;

			virtual double separationWeight() const = 0;
			virtual double cohesionWeight() const = 0;
			virtual double alignmentWeight() const = 0;

			virtual double seekWeight() const = 0;
			virtual double wanderWeight() const = 0;
			virtual double fleeWeight() const = 0;

			virtual double wallDetectionFeelerLength() const = 0;
			virtual double obstacleAvoidanceWeight() const = 0;

			virtual float mass() const = 0;
			virtual float maxForce() const = 0;
			virtual float maxTurnRate() const = 0;
			virtual float maxSpeed() const = 0;

			virtual kmint::play::actor& persuitTarget() const = 0;
			virtual kmint::play::actor& fleeTarget() const = 0;
		};
	}
}
