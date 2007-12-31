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
 
typedef struct cpHashSetBin {
	void *elt;
	unsigned long hash;
	struct cpHashSetBin *next;
} cpHashSetBin;

typedef int (*cpHashSetEqlFunc)(void *ptr, void *elt);
typedef void *(*cpHashSetTransFunc)(void *ptr, void *data);
typedef void (*cpHashSetIterFunc)(void *elt, void *data);
typedef int (*cpHashSetRejectFunc)(void *elt, void *data);

typedef struct cpHashSet {
	int entries, size;
	cpHashSetEqlFunc eql;
	
	cpHashSetTransFunc trans;
	
	void *default_value;
	
	cpHashSetBin **table;
} cpHashSet;

void cpHashSetDestroy(cpHashSet *set);
void cpHashSetFree(cpHashSet *set);

cpHashSet *cpHashSetAlloc(void);
cpHashSet *cpHashSetInit(cpHashSet *set, int size, cpHashSetEqlFunc eqlFunc, cpHashSetTransFunc trans);
cpHashSet *cpHashSetNew(int size, cpHashSetEqlFunc eqlFunc, cpHashSetTransFunc trans);

void cpHashSetResize(cpHashSet *set);

void *cpHashSetInsert(cpHashSet *set, unsigned long hash, void *ptr, void *data);
void *cpHashSetRemove(cpHashSet *set, unsigned long hash, void *ptr);
void *cpHashSetFind(cpHashSet *set, unsigned long hash, void *ptr);

void cpHashSetEach(cpHashSet *set, cpHashSetIterFunc func, void *data);
void cpHashSetReject(cpHashSet *set, cpHashSetRejectFunc func, void *data);
