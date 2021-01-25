using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharp
{
    public class operations
    {
        public static Func<int, int, int> add = (x, y) => x + y;
        public static Func<int, int, int> sub = (x, y) => x - y;
        //public static Func<int,int,int> mul=()
    }

    public class segment_tree<T> where T:struct, IComparable, IComparable<T>
    {
        T dfval = default(T);
        Func<T, T, T> m_operation;
        T[] m_tree, m_lazy;

        segment_tree(Func<T, T, T> operation) => m_operation = operation;

        public void init(int[] items)
        {            

        }

        public void update(int nodeid, int ss, int se, int pos, T val)
        {
            update(nodeid, ss, se, pos, pos, val);
        }

        public void update(int nodeid, int ss, int se, int rs, int re, T val)
        {
            
            if (ss > re || se < rs) return;
            int mid = (ss + se) / 2, lchild = 2 * nodeid + 1, rchild = 2 * nodeid + 2;
            //if (m_lazy[nodeid].CompareTo()) ;
        }
        private void setSize(int size) {
            int newTreeSize = 2 * (int)(Math.Pow(2, Math.Ceiling(Math.Log10(size) / Math.Log10(2)) + 1));
            m_tree = new T[newTreeSize];
            m_lazy = new T[newTreeSize];
        }

        private void build(T[] items, int nodeid, int ss, int se)
        {
            if(se==ss) { m_tree[nodeid] = items[ss]; }
            else
            {
                build(items, 2 * nodeid + 1, ss, (ss + se) / 2);
                build(items, 2 * nodeid + 2, ((ss + se) / 2) + 1, se);
                m_tree[nodeid] = m_operation(m_tree[2 * nodeid + 1], m_tree[2 * nodeid + 2]);
            }
        }


    }
}
