#include "vector.h"             // inkludera din headerfil här
#include <assert.h>             // assert(b) ger felmeddelande om b falsk
#include <cxxtest/TestSuite.h>
#include <stdexcept>
#include <iostream>


class VectorTestSuite : public CxxTest::TestSuite {
    public:
        /**
         * Test constructors for initialisation.
         */
        void test_init()
        {
            Vector<unsigned int> a(0);
            TS_ASSERT(a.size() == 0);
            Vector<unsigned int> b(1);
            TS_ASSERT(b.size() == 1);
            Vector<unsigned int> c(123);
            TS_ASSERT(c.size() == 123);

            Vector<unsigned int> d(c);
            TS_ASSERT(d.size() == c.size());
            Vector<unsigned int> e = c;
            TS_ASSERT(e.size() == c.size());

            /* Vector<unsigned int> f(3); */
            /* TS_ASSERT(f[0] == 0); */
            /* TS_ASSERT(f[1] == 0); */
            /* TS_ASSERT(f[2] == 0); */

            const Vector<unsigned int> constA(10);
            TS_ASSERT(constA.size() == 10);

            Vector<unsigned int> g(10, 7);
            TS_ASSERT(g.size() == g.size());
            for (unsigned int i = 0; i < g.size(); ++i)
                TS_ASSERT(g[i] == 7);
        }

        /**
         * Test assignment
         */
        void test_assign()
        {
            Vector<unsigned int> a(10);
            a[0] = 1;
            a[9] = 2;
            Vector<unsigned int> b = a;
            TS_ASSERT(b[0] == 1);
            TS_ASSERT(b[9] == 2);

            Vector<unsigned int> c(5);
            c[1] = 3;
            c[2] = 4;
            int x = c[1];
            int y = c[2];
            TS_ASSERT(x == 3);
            TS_ASSERT(y == 4);

            Vector<unsigned int> d(10);
            d[5] = 10;
            d[5]++;
            TS_ASSERT(d[5] == 11);
        }

        /**
         * Test clearing.
         */
        void test_clear()
        {
            Vector<unsigned int> a(5);
            for (unsigned int i = 0; i < a.size(); ++i)
                a[i] = i;
            a.clear();
            for (unsigned int i = 0; i < a.size(); ++i)
                TS_ASSERT(a[i] == 0);
        }

        /**
         * Test the push back functionality.
         */
        void test_push_back()
        {
            Vector<unsigned int> a(13);
            a.push_back(5);
            TS_ASSERT_EQUALS(a[13], (unsigned int) 5);
            TS_ASSERT_EQUALS(a[10], (unsigned int) 0);

            Vector<unsigned int> b(a);
            TS_ASSERT_EQUALS(b[13], (unsigned int) 5);
            /* TS_ASSERT_EQUALS(b[9], (unsigned int) 0); */

            a.push_back(17);
            TS_ASSERT_EQUALS(a[14], (unsigned int) 17);
            TS_ASSERT_THROWS(b[14], std::out_of_range);

            Vector<unsigned int> c(0);
            c.push_back(1);
            c.push_back(2);
            c.push_back(3);
            TS_ASSERT_EQUALS(c[1], (unsigned int) 2);
            c[0] = 5;
            TS_ASSERT_EQUALS(c[0], (unsigned int) 5);
        }

        /**
         * Test copy.
         */
        void test_copy_op()
        {
            Vector<unsigned int> a(5);
            a[2] = (unsigned int) 3;
            Vector<unsigned int> b(7);
            b = a;
            TS_ASSERT_EQUALS(b[2], (unsigned int) 3);
            TS_ASSERT_EQUALS(a[2], (unsigned int) 3);
            TS_ASSERT(b.size() == 5);

            a.push_back(19);
            TS_ASSERT_THROWS(b[5], std::out_of_range);

            a[2] = (unsigned int) 4;
            TS_ASSERT_EQUALS(b[2], (unsigned int) 3);
            TS_ASSERT_EQUALS(a[2], (unsigned int) 4);

            b[2] = (unsigned int) 5;
            TS_ASSERT_EQUALS(b[2], (unsigned int) 5);
            TS_ASSERT_EQUALS(a[2], (unsigned int) 4);
        }

        /**
         * Self copy test.
         */
        void test_copy_self()
        {
            Vector<unsigned int> a(4);
            a[1] = 8;
            a = a;
            TS_ASSERT(a[1] == 8);
            /* TS_ASSERT(a[0] == 0); */
        }

        /**
         * Test the initializer list.
         */
        void test_initializer_list()
        {
            Vector<unsigned int> a({4,5,6});
            TS_ASSERT(a.size() == 3);
            TS_ASSERT(a[0] == 4);
            TS_ASSERT(a[1] == 5);
            TS_ASSERT(a[2] == 6);
        }

        /**
         * Test copy assignment where the array sizes differ.
         */
        void test_copy_assign_diffsize()
        {
            Vector<unsigned int> a(5);
            a[4] = 1;
            Vector<unsigned int> b(2);
            b = a;
            TS_ASSERT(b[4] == 1);

            Vector<unsigned int> c(12);
            c[10] = 2;
            Vector<unsigned int> d(20);
            d[19] = 3;
            d[10] = 4;
            c = d;
            TS_ASSERT(c[19] == 3);
            TS_ASSERT(c[10] == 4);
        }

        /**
         * Test going out-of-bounds.
         */
        void test_index_except()
        {
            Vector<unsigned int> a(5);
            const Vector<unsigned int> b(1);
            TS_ASSERT_THROWS(a[5] = 1, std::out_of_range);
            TS_ASSERT_THROWS(b[2], std::out_of_range);
        }

        /**
         * Test to push_back over the internal capacity.
         */
        void test_push_back_lots()
        {
            Vector<unsigned int> a(0); // Should default to internal size 10
            for (int i = 0; i < 20; ++i)
                a.push_back(i);

            TS_ASSERT(a[9] == 9);
            TS_ASSERT(a[10] == 10);
            TS_ASSERT(a[15] == 15);
            TS_ASSERT(a[19] == 19);
        }

        /**
         * Verify that exceptions are thrown if type is not move
         * assignable/constructable.
         */
        void test_move_assignable_constructable()
        {
            // Uncomment to get compile error
            /* Vector<int[]>(); */
        }

        /**
         * Copy of inital tests.
         */
        void test_old()
        {
            Vector<double> v;           // ok: defaultkonstruktor ger vektor med flyttal
            Vector<char> *a = new Vector<char>[3];  // dynamiskt allokerade ser ut så här
            delete [] a;

            assert(v.size() == 0);      // tom från början
            v.push_back(3.14);          // lägg till ett element sist 
            assert(v.size() == 1);      // nu ligger ett element i vektorn
            v.insert(0, 2.10);          // lägg till före element 0, dvs först
            assert(v[0] == 2.10 &&      // hamnade de rätt?
	           v[1] == 3.14);
            assert(v.size() == 2);      // nu ligger två element i vektorn
/*
            v.sort(false);              // sortera i fallande ordning
            assert(v[0] == 3.14 &&      // hamnade de rätt?
	           v[1] == 2.10);       
            assert(v.size() == 2);      // ingenting ändrat?
            v[1] = 2.11;                // tilldelning av enstaka element;

            const Vector<double> &vc = v;  // skapa konstant referens
            assert(vc.size() == 2);     // ok: ändrar ej vektorn som är konstant
            assert(vc[0] == 3.14 &&     // ok: ändrar ej vektorn som är konstant
	           vc[1] == 2.11);
*/
            
            v.erase(0);                 // ta bort första elementet               
            assert(v.size() == 1);      // rätt antal elelment
            v.clear();                  // töm hela vektorn
            assert(v.size() == 0);      // tom när alla element är borttagna
            
            // kontrollera att följande rader inte går att kompilera
            //vc[0] = 3.1415;             // fel: tilldelning av konstant objekt
            //Vector<char> c = v;         // fel: tilldelning av olika typer
        }
};
