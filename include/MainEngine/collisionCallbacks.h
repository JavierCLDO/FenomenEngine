#pragma once

#include "entity.h"

namespace fenomen::logic::callbacks {

	static void OnTriggerEnter(Entity* e1, Entity* e2) { 
		e1->OnTriggerEnter(e2); e2->OnTriggerEnter(e1);
	}

	static void OnTriggerExit(Entity* e1, Entity* e2) {
		e1->OnTriggerExit(e2); e2->OnTriggerExit(e1);
	}

	static void OnCollision(Entity* e1, Entity* e2) { 
		e1->OnCollision(e2); e2->OnCollision(e1);
	}

	static void OnCollisionSeparated(Entity* e1, Entity* e2) {
		e1->OnCollisionSeparated(e2); e2->OnCollisionSeparated(e1);
	}
}
