package main

import (
	"fmt"

	"gopkg.in/mgo.v2"
	"gopkg.in/mgo.v2/bson"
)

//插入操作
func Insert_MongoDB(c *mgo.Collection) {
	//创建people同时向person表插入数据
	err := c.Insert(&Person{"Ale", "111111"}, &Person{"Cla", "222222222"})
	if err != nil {
		panic(err)
	}
}

//根据条件查询
func Select_One_Result(c *mgo.Collection) {
	result := Person{}
	//按照条件进行查询
	//bson.M{} 这个东西是整个mgo的明星东东.用来把golang的结构转bson的东东.
	err := c.Find(bson.M{"name": "Ale"}).One(&result)
	if err != nil {
		panic(err)
	}
	fmt.Println("Phone:", result.Phone)
}

//查询所有记录
func Select_All_Result(c *mgo.Collection) {
	resultArry := []Person{}
	err := c.Find(bson.M{}).All(&resultArry) //或者err = c.Find(nil).All(&resultArry)
	if err != nil {
		panic(err)
	}
	for _, rst := range resultArry {
		fmt.Println("Phone:", rst.Phone)
		fmt.Println("Name:", rst.Name)
	}
}

//更新数据
func Update_MongoDB(c *mgo.Collection) {
	//更新整条数据
	//err := c.Update(bson.M{"name": "Ale"}, bson.M{"name": "guo"})
	//更新一条数据的某个字段
	err := c.Update(bson.M{"name": "Ale"}, bson.M{"$set": bson.M{"name": "guo"}})
	if err != nil {
		panic(err)
	}
}

//删除条件获取中的一条数据
func Remove_MongoDB(c *mgo.Collection) {
	err := c.Remove(bson.M{"name": "Ale"})
	if err != nil {
		panic(err)
	}
}

//删除根据条件获取结果中的所有数据
func RemoveAll_MongoDB(c *mgo.Collection) {
	_, err := c.RemoveAll(bson.M{"name": "Cla"})
	if err != nil {
		panic(err)
	}
}

//获取数据条数
func Count_MongoDB(c *mgo.Collection) {
	count, err := c.Find(bson.M{"name": "Cla"}).Count()
	if err != nil {
		panic(err)
	}
	fmt.Println("count:", count)
}

//获取集合中所有数据
func CountAll_MongoDB(c *mgo.Collection) {
	count, err := c.Find(bson.M{}).Count() //c.Find(nil).Count()
	if err != nil {
		panic(err)
	}
	fmt.Println("count:", count)
}
