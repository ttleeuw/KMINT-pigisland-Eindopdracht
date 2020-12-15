#include "kmint/pigisland/entities/pig.hpp"
#include "kmint/pigisland/resources/resources.hpp"
#include "kmint/random.hpp"

namespace kmint {
    namespace pigisland {
        pig::pig(math::vector2d location)
          : play::free_roaming_actor{location}, drawable_{*this, pig_image()} 
        {
			
        }

		void pig::move() {
			
		}
    } // namespace pigisland
} // namespace kmint
