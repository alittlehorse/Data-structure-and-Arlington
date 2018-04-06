"""OK，头结点的链表实现成功
哈哈哈哈美滋滋
"""
#这是链式表，O(n)，但是存储的密度低
#顺序表就是数组，可以做到序号随机访问，O(1)
#如果常做查找操作，选择顺序表，相反，选择链表
class Node:
    def __init__(self,data):
        """
        node 初始化
        ：para data：节点数据
        """
        self.data = data
        self.pnext=None
    def __repr__(self):
        return str(self.data)

class LinkedList:
    def __init__(self):
        "linked list 的初始化"
    #头结点不算长度
        self.length = 0
        head_node=Node(data=None)
        self.head = head_node

    def is_empty(self):
        return self.length==0
    def __len__(self):
        return self.length

    #无头结点
    def append(self,this_node):
        """
        在链表末尾添加node值，如果node对象直接添加，否则先转换为node对象
        ：param this_node：数据或者对象
        ：return：Node
        """
        if isinstance(this_node,Node):
            pass
        else:
            this_node=Node(data=this_node)
        node = self.head#指出头结点
        while node.pnext:
            node = node.pnext
        node.pnext=this_node
        self.length+=1


    #   get必须可以get到头结点
    def get(self,index):
        if len(self )<index or index<0:
            return None
        node =self.head
        while index :
            node=node.pnext
            index-=1
        return node
    #set 不可以更改头结点
    def set(self,index,data):
        if index!=0:
            node =self.get(index)
            if node :
                node.data =data
            return node
        else:
            return None
    #头插法
    def insert(self,index,data):
        node = Node(data)
        if index>len(self) or index<=0:
            return False
        pre = self.get(index-1)
        temp_node = pre.pnext
        pre.pnext=node
        node.pnext = temp_node
        self.length+=1



    def delete(self,index):
        if len(self)<index or index<=0:
            return  False
        pre =self.get(index-1)
        node=self.get(index)
        temp_node =node.pnext
        pre.pnext=temp_node
        node.pnext=None
        self.length-=1
    #O(length(L))逆序构造，和原有的链表相同

    def Create_L_tail(self,n):
        p = self.head
        for i in range(n):
            item = input("please input your items:")
            node=Node(item)
            node.pnext=p.pnext
            p.pnext=node
            self.length+=1
    #   O(1)顺序构造 和原有的顺序相反
    def Create_L_head(self):
        p=self.head
        item = input("please input your items:")
        while(item!="flag"):
            node = Node(item)
            p.pnext=node
            p=node
            self.length+=1
            item = input("please input your items:")
    # 遍历

    # 合并
    #有序逆序合并
    def union(self,L):
        nl = LinkedList()
        pc=nl.head.pnext
        pa=self.head.pnext
        pb = L.head.pnext
        temp = Node(None)
        while pa or pb:

            if pa ==None:
                temp=pb
                pb= pb.pnext
            elif pb==None:
                temp=pa
                pa=pa.pnext
            elif pa.data<=pb.data:
                temp=pa
                pa=pa.pnext
            else :
                temp=pb
                pb=pb.pnext
            temp.pnext = pc
            pc=temp

        return nl

    # 分解

    # 逆序
    def inverse(self):
        p=self.head.pnext;L=self.head ;L.pnext=None
        while p:
            succ =p.pnext
            p.pnext = L.pnext
            L.pnext=p
            p=succ
#有序表





#s->next =p_.next; p->next =s s->next->prior =  s;s->prior =p
#这四步并不是任意变化的，只要可以通过其他两个节点可以找到第四个节点的位置，就可以变化
class DuLNode:
    def __index__(self,data):
        self.data = data
        self.prior=None
        self.pnext =None





if __name__=="__main__":
    linklist1 =LinkedList()
    linklist1.Create_L_head()
    linklist2 = LinkedList()
    linklist2.Create_L_head()

    l3=linklist1.union(linklist2)
    print(l3.get(1))




        