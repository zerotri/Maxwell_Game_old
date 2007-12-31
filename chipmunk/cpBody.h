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
 
typedef struct cpBody{
	cpFloat m, m_inv; /* mass and mass inverse */
	cpFloat i, i_inv; /* moment of inertia and its inverse */
	
	/* linear components */
	cpVect p, v, f, v_bias; /* position, velocity and force */
	/* angular components */
	cpFloat a, w, t, w_bias; /* angle, angular velocity, and torque */
	cpVect rot; /* object rotation as a unit length vector */
	
//	int active;
} cpBody;

cpBody *cpBodyAlloc(void);
cpBody *cpBodyInit(cpBody *body, cpFloat m, cpFloat i);
cpBody *cpBodyNew(cpFloat m, cpFloat i);

void cpBodyDestroy(cpBody *body);
void cpBodyFree(cpBody *body);

void cpBodyUpdateVelocity(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt);
void cpBodyUpdatePosition(cpBody *body, cpFloat dt);

static inline void
cpBodyApplyImpulse(cpBody *body, cpVect j, cpVect r)
{
	body->v = cpvadd(body->v, cpvmult(j, body->m_inv));
	body->w += body->i_inv*cpvcross(r, j);
}

static inline void
cpBodyApplyBiasImpulse(cpBody *body, cpVect j, cpVect r)
{
	body->v_bias = cpvadd(body->v_bias, cpvmult(j, body->m_inv));
	body->w_bias += body->i_inv*cpvcross(r, j);
}

void cpBodyResetForces(cpBody *body);
void cpBodyApplyForce(cpBody *body, cpVect f, cpVect r);

void cpBodySetMass(cpBody *body, cpFloat m);
void cpBodySetMoment(cpBody *body, cpFloat i);
void cpBodySetAngle(cpBody *body, cpFloat a);

void cpDampedSpring(cpBody *a, cpBody *b, cpVect anchr1, cpVect anchr2, cpFloat rlen, cpFloat k, cpFloat dmp, cpFloat dt);

//int cpBodyMarkLowEnergy(cpBody *body, cpFloat dvsq, int max);
