#pragma once

#include "kmint/pigisland/entities/properties/IProperties.hpp"

namespace kmint {
	namespace pigisland {
		class PigPropertiesDefault : public IProperties {
		private:
			double _wanderJitter;
			double _wanderRadius;
			double _wanderDistance;

			double _separationWeight;
			double _cohesionWeight;
			double _alignmentWeight;

			double _seekWeight;
			double _persuitWeight;
			double _wanderWeight;
			double _fleeWeight;

			double _wallDetectionFeelerLength;
			double _obstacleAvoidanceWeight;

			double _mass;
			double _maxForce;
			double _maxTurnRate;
			double _maxSpeed;

			kmint::play::actor& _persuitTarget;
			kmint::play::actor& _fleeTarget;
		public:
			PigProperties(kmint::play::actor& boat, kmint::play::actor& shark) : _persuitTarget(boat), _fleeTarget(shark) {}

			double wanderJitter() const override { return _wanderJitter; };
			double wanderRadius() const override { return _wanderRadius; };
			double wanderDistance() const override { return _wanderDistance; };

			double separationWeight() const override { return _separationWeight; };
			double cohesionWeight() const override { return _cohesionWeight; };
			double alignmentWeight() const override { return _alignmentWeight; };

			void setSeparationWeight(double seperationWeight) { _separationWeight = seperationWeight; };
			void setCohesionWeight(double cohesionWeight) { _cohesionWeight = cohesionWeight; };
			void setAlignmentWeight(double allignmentWeight) { _alignmentWeight = allignmentWeight; };


			double seekWeight() const override { return _seekWeight; }
			double persuitWeight() const override { return _persuitWeight; }
			double wanderWeight() const override { return _wanderWeight; }
			double fleeWeight() const override { return _fleeWeight; }

			void setSeekWeight(double seekWeight) { _seekWeight = seekWeight; };
			void setPersuitWeight(double persuitWeight) { _persuitWeight = persuitWeight; };
			void setwanderWeight(double wanderWeight) { _wanderWeight = wanderWeight; };
			void setFleeWeight(double fleeWeight) { _fleeWeight = fleeWeight; };


			double wallDetectionFeelerLength() const override { return _wallDetectionFeelerLength; };
			double obstacleAvoidanceWeight() const override { return _obstacleAvoidanceWeight; };

			float mass() const override { return _mass; };
			float maxForce() const override { return _maxForce; };
			float maxTurnRate() const override { return _maxTurnRate; };
			float maxSpeed() const override { return _maxSpeed; };
		};
	}
}