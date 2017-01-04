/*
 * Copyright 2017 Raefaldhi Amartya Junior <raefaldhiamartya@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
 
#ifndef Query_H
#define Query_H

#include <Query.h>

class Query : public BQuery {
public:
	static Query* instance;

	static void Init();
private:
	Query();
};

#endif // Query_H
