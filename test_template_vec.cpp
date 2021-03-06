#include "kth_cprog_template_container.hpp"
#include <assert.h>
#include <cxxtest/TestSuite.h>
#include <stdexcept>
#include <iostream>
#include <iterator>


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
            Vector<unsigned int> h(1024);
            TS_ASSERT(h.size() == 1024);

            Vector<unsigned int> d(c);
            TS_ASSERT(d.size() == c.size());
            Vector<unsigned int> e = c;
            TS_ASSERT(e.size() == c.size());

            const Vector<unsigned int> constA(10);
            TS_ASSERT(constA.size() == 10);

            Vector<unsigned int> g(10, 7);
            TS_ASSERT(g.size() == g.size());
            for (unsigned int i = 0; i < g.size(); ++i)
                TS_ASSERT(g[i] == 7);
        }

        /**
         * Test the vector size.
         */
        void test_size()
        {
            Vector<int> a;
            Vector<int> b(10);
            Vector<int> c(20, 8);

            TS_ASSERT(a.size() == 0);
            TS_ASSERT(b.size() == 10);
            TS_ASSERT(c.size() == 20);

            // Should double the capacity
            for (unsigned int i = 0; i < 5; ++i, a.insert(0, 1));
            TS_ASSERT(a.size() == 5);

            for (unsigned int i = 0; i < b.size(); b[i] = 10, ++i);
            TS_ASSERT(b.size() == 10);

            for (unsigned int i = 0; i < 5; ++i, c.erase(0));
            TS_ASSERT(c.size() == 15);
        }

        /**
         * Test the vector capacity.
         */
        void test_capacity()
        {
            Vector<int> a;
            Vector<int> b(5);
            Vector<int> c(10);
            Vector<int> d(11);
            Vector<int> e(20, 123);

            TS_ASSERT(a.capacity() == 10);
            TS_ASSERT(b.capacity() == 10);
            TS_ASSERT(c.capacity() == 10);
            TS_ASSERT(d.capacity() == 11);
            TS_ASSERT(e.capacity() == 20);

            // Should double the capacity
            for (unsigned int i = 0; i < 5; ++i, b.insert(0, 1));
            TS_ASSERT(b.capacity() == 10);
            b.insert(0, 1);
            TS_ASSERT(b.capacity() == 20);
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
         * Test resetting.
         */
        void test_reset()
        {
            Vector<unsigned int> a(5);
            for (std::size_t i = 0; i < a.size(); ++i)
                a[i] = i;
            a.reset();
            for (std::size_t i = 0; i < a.size(); ++i)
                TS_ASSERT(a[i] == 0);
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
            TS_ASSERT(a.size() == 0);
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

        void test_insert()
        {
            Vector<int> v(9, 1);
            v.insert(0, 2);
            TS_ASSERT(v[0] == 2);
            for (unsigned int i = 1; i < v.size(); ++i)
                TS_ASSERT(v[i] == 1);
            v.insert(5, 3);
            TS_ASSERT(v[5] == 3);
            v.insert(10, 4);
            TS_ASSERT(v[10] == 4);

            Vector<int> w(5, 8);
            w.insert(4, 1);
            TS_ASSERT(w[4] == 1);
            for (unsigned int i = 0; i < w.size() - 2; ++i)
                TS_ASSERT(w[i] == 8);

            w.insert(w.size(), 33);
            TS_ASSERT(w[w.size()-1] == 33);

            Vector<int> v2;
            for (int i = 0; i < 3; ++i)
            {
                v2.insert(0, 42);
                v2.insert(0, -43);
                v2.insert(1, 44);
                v2.insert(3, 45);
            }
            for (int i = 0; i < 3; ++i)
            {
                TS_ASSERT(v2[i * 4] == -43);
                TS_ASSERT(v2[i * 4 + 1] == 44);
                TS_ASSERT(v2[i * 4 + 2] == 42);
                TS_ASSERT(v2[i * 4 + 3] == 45);
            }
        }

        void test_iterator()
        {
            Vector<int> v({2,3,4,5,6});
            int i = 2;
            for( VectorIterator<int> it = v.begin(); it != v.end(); ++it )
            {
                TS_ASSERT_EQUALS( *it, i++ );
            }

            VectorIterator<int> it2 = v.find(5);
            TS_ASSERT_EQUALS( *it2, 5);
            it2 = v.find(3);
            TS_ASSERT_EQUALS( *it2, 3 );

            VectorIterator<int> it3 = v.end();
            it3--;
            TS_ASSERT_EQUALS( *it3, 6 );

            std::iterator<std::random_access_iterator_tag, int>::difference_type diff = it3 - it2;
            it2 = it2 + diff;
            TS_ASSERT_EQUALS( it2, it3 );
        }

        void test_const_iterator()
        {
            const Vector<int> v({2,3,4,5,6});
            int i = 2;
            for( VectorIterator<int> it = v.begin(); it != v.end(); ++it )
            {
                TS_ASSERT_EQUALS( *it, i++ );
            }

            VectorIterator<int> it2 = v.find(5);
            TS_ASSERT_EQUALS( *it2, 5);
            it2 = v.find(3);
            TS_ASSERT_EQUALS( *it2, 3 );

            VectorIterator<int> it3 = v.end();
            it3--;
            TS_ASSERT_EQUALS( *it3, 6 );

            std::iterator<std::random_access_iterator_tag, int>::difference_type diff = it3 - it2;
            it2 = it2 + diff;
            TS_ASSERT_EQUALS( it2, it3 );
        }

        /**
         * Test the erase function of the vector.
         */
        void test_erase()
        {
            Vector<int> a({1,2,3,4,5});
            Vector<int> b(10);
            Vector<int> c(2, 9);

            a.erase(2);
            TS_ASSERT(a[0] == 1);
            TS_ASSERT(a[1] == 2);
            TS_ASSERT(a[2] == 4);
            TS_ASSERT(a[3] == 5);
            TS_ASSERT(a.size() == 4);

            b.erase(9);
            TS_ASSERT(b.size() == 9);

            unsigned int size = c.size();
            for (unsigned int i = 0; i < size; ++i, c.erase(0));
            TS_ASSERT(c.size() == 0);
        }

        /**
         * Test constructing vector with const size_t
         */
        void test_const_size()
        {
            const size_t s = 17;
            Vector<int> a(s);
            TS_ASSERT_EQUALS(a.size(), (std::size_t) 17);
        }

        // shouldn't compile
//        void test_stuff()
//        {
//            std::size_t n = 24;
//            UIntVector a(1);
//            a = n;
//            TS_ASSERT(a.size() != n);
//            UIntVector b = n;
//            TS_ASSERT(b.size() != n);
//        }

        /**
         * Tests for memory leak
         */
        void test_mem_leak()
        {
            Vector<unsigned int> v(20);
            for(unsigned int i = 0; i < 100000; ++i)
                v.push_back(i);
            TS_ASSERT_EQUALS(v.size(), (std::size_t) 100020);
            Vector<unsigned int> u = std::move(v);
            v = u;
            Vector<unsigned int> * w = new Vector<unsigned int>(7);
            delete w;

            Vector<unsigned int> a(123232);
            a = v;

            Vector<unsigned int> b(2);
            a.reset();
            b = std::move(a);
        }

        /**
         * Copy of inital tests.
         */
        void test_old()
        {
            Vector<double> v;           // ok: defaultkonstruktor ger vektor med flyttal
            Vector<char> *a = new Vector<char>[3];  // dynamiskt allokerade ser ut s� h�r
            delete [] a;

            assert(v.size() == 0);      // tom fr�n b�rjan
            v.push_back(3.14);          // l�gg till ett element sist
            assert(v.size() == 1);      // nu ligger ett element i vektorn
            v.insert(0, 2.10);          // l�gg till f�re element 0, dvs f�rst
            assert(v[0] == 2.10 &&      // hamnade de r�tt?
               v[1] == 3.14);
            assert(v.size() == 2);      // nu ligger tv� element i vektorn

            std::sort(v.begin(), v.end(), [](double a, double b){return a > b;});
            /* v.sort(false);              // sortera i fallande ordning */
            assert(v[0] == 3.14 &&      // hamnade de r�tt?
                v[1] == 2.10);
            assert(v.size() == 2);      // ingenting �ndrat?
            v[1] = 2.11;                // tilldelning av enstaka element;

            const Vector<double> &vc = v;  // skapa konstant referens
            assert(vc.size() == 2);     // ok: �ndrar ej vektorn som �r konstant
            assert(vc[0] == 3.14 &&     // ok: �ndrar ej vektorn som �r konstant
                vc[1] == 2.11);

            v.erase(0);                 // ta bort f�rsta elementet
            assert(v.size() == 1);      // r�tt antal elelment
            v.clear();                  // t�m hela vektorn
            assert(v.size() == 0);      // tom n�r alla element �r borttagna

            // kontrollera att f�ljande rader inte g�r att kompilera
            //vc[0] = 3.1415;             // fel: tilldelning av konstant objekt
            //Vector<char> c = v;         // fel: tilldelning av olika typer
        }
};
