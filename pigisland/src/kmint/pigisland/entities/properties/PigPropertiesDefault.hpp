#pragma once

#include "kmint/pigisland/entities/properties/IProperties.hpp"

namespace kmint {
	namespace pigisland {
		class PigPropertiesDefault : public IProperties {
		private:
			kmint::play::actor& _pursuitTarget;
			kmint::play::actor& _fleeTarget;
		public:
			PigPropertiesDefault(kmint::play::actor& boat, kmint::play::actor& shark) : _pursuitTarget{ boat }, _fleeTarget{ shark } {}

			double wanderJitter() const override { return 8; };
			double wanderRadius() const override { return 16; };
			double wanderDistance() const override { return 32; };

			double separationWeight() const override { return 1; };
			double cohesionWeight() const override { return 1; };
			double alignmentWeight() const override { return 1; };

			double seekWeight() const override { return 1; }
			double wanderWeight() const override { return 1; }
			double fleeWeight() const override { return 1; }

			double wallDetectionFeelerLength() const override { return 32; };
			double obstacleAvoidanceWeight() const override { return 10; };

			float mass() const override { return 5; };
			float maxForce() const override { return 20; };
			float maxTurnRate() const override { return 20; };
			float maxSpeed() const override { return 25; };

			kmint::play::actor& persuitTarget() const override { return _pursuitTarget; }
			kmint::play::actor& fleeTarget() const override { return _fleeTarget; }
		};
	}
}