/* Copyright (c) 2007 Scott Lembcke
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
 
extern cpFloat cp_bias_coef;
extern cpFloat cp_collision_slop;

typedef struct cpContact{
	cpVect p, n;
	cpFloat dist;
	
	cpVect r1, r2;
	cpFloat nMass, tMass;

	cpFloat jnAcc, jtAcc, jBias;
	cpFloat bias, bounce;
	
	unsigned long hash;
} cpContact;

//cpContact* cpContactAlloc(void);
cpContact* cpContactInit(cpContact *con, cpVect p, cpVect n, cpFloat dist, unsigned int hash);
//cpContact* cpContactNew(cpVect p, cpVect n, cpFloat dist, unsigned int hash);

//void cpContactDestroy(cpContact *con);
//void cpContactFree(cpContact *con);

cpVect cpContactsSumImpulses(cpContact *contacts, int numContacts);
cpVect cpContactsSumImpulsesWithFriction(cpContact *contacts, int numContacts);

typedef struct cpArbiter{
	int numContacts;
	cpContact *contacts;
	cpShape *a, *b;
	cpFloat u, e;
	cpVect target_v;
	
	int stamp;
} cpArbiter;

cpArbiter* cpArbiterAlloc(void);
cpArbiter* cpArbiterInit(cpArbiter *arb, cpShape *a, cpShape *b, int stamp);
cpArbiter* cpArbiterNew(cpShape *a, cpShape *b, int stamp);

void cpArbiterDestroy(cpArbiter *arb);
void cpArbiterFree(cpArbiter *arb);

void cpArbiterInject(cpArbiter *arb, cpContact *contacts, int numContacts);
void cpArbiterPreStep(cpArbiter *arb, cpFloat dt_inv);
void cpArbiterApplyImpulse(cpArbiter *arb);
