#pragma once

#include "kmint/pigisland/entities/properties/IProperties.hpp"

namespace kmint {
	namespace pigisland {
		class PigPropertiesGenetic : public IProperties {
		private:
			kmint::play::actor& _persuitTarget;
			kmint::play::actor& _fleeTarget;

			double _separationWeight;
			double _cohesionWeight;
			double _alignmentWeight;

			double _seekWeight;
			double _fleeWeight;
		public:
			PigPropertiesGenetic(kmint::play::actor& boat, kmint::play::actor& shark) : _persuitTarget{ boat }, _fleeTarget{ shark } {}

			double wanderJitter() const override { return 8; };
			double wanderRadius() const override { return 16; };
			double wanderDistance() const override { return 32; };

			double separationWeight() const override { return _separationWeight; };
			double cohesionWeight() const override { return _cohesionWeight; };
			double alignmentWeight() const override { return _alignmentWeight; };

			void setSeparationWeight(double seperationWeight) { _separationWeight = seperationWeight; };
			void setCohesionWeight(double cohesionWeight) { _cohesionWeight = cohesionWeight; };
			void setAlignmentWeight(double allignmentWeight) { _alignmentWeight = allignmentWeight; };

			double seekWeight() const override { return _seekWeight; }
			double wanderWeight() const override { return 1; }
			double fleeWeight() const override { return _fleeWeight; }

			void setSeekWeight(double seekWeight) { _seekWeight = seekWeight; };
			void setFleeWeight(double fleeWeight) { _fleeWeight = fleeWeight; };

			double wallDetectionFeelerLength() const override { return 64; };
			double obstacleAvoidanceWeight() const override { return 15; };

			float mass() const override { return 5; };
			float maxForce() const override { return 20; };
			float maxTurnRate() const override { return 20; };
			float maxSpeed() const override { return 25; };

			kmint::play::actor& persuitTarget() const override { return _persuitTarget; }
			kmint::play::actor& fleeTarget() const override { return _fleeTarget; }
		};
	}
}