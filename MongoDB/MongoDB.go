package main

import (
	"gopkg.in/mgo.v2"
	//"gopkg.in/mgo.v2/bson"
)

type Person struct {
	Name  string
	Phone string
}

func main() {
	//与MongoDB建立连接
	session, err := mgo.Dial("")
	if err != nil {
		panic(err)
	}
	defer session.Close()

	session.SetMode(mgo.Monotonic, true)
	//切换到test数据库的people表
	c := session.DB("test").C("people")

	//插入数据操作
	Insert_MongoDB(c)

	//根据条件查询
	Select_One_Result(c)

	//查询所有记录
	Select_All_Result(c)

	//更新
	Update_MongoDB(c)

	//根据条件进行删除查询结果中一条数据
	Remove_MongoDB(c)

	//删除所有数据
	RemoveAll_MongoDB(c)

	//根据条件获取所有数据条数
	Count_MongoDB(c)

	//获取集合中所有数据
	CountAll_MongoDB(c)

}
