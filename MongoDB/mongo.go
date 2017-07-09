package mongo

import (
	"gopkg.in/mgo.v2"
	"time"
)

var _url string
var _username string
var _password string

func getC(dbName string, coName string) (*mgo.Session, *mgo.Collection, error) {
	dialInfo := &mgo.DialInfo{
		Addrs:     []string{_url},
		Direct:    false,
		Timeout:   time.Second * 10,
		Database:  "",
		Source:    "admin",
		Username:  _username,
		Password:  _password,
		PoolLimit: 4096, // Session.SetPoolLimit
	}

	session, err := mgo.DialWithInfo(dialInfo)

	if err != nil {
		return nil, nil, err
	}

	session.SetMode(mgo.Eventual, true)

	db := session.DB(dbName)
	collection := db.C(coName)

	return session, collection, nil
}

func Config(url string, username string, password string) {
	_url = url
	_username = username
	_password = password
}

func Insert(dbName string, coName string, document interface{}) error {
	session, c, err := getC(dbName, coName)
	if err != nil {
		return err
	}
	defer session.Close()

	err = c.Insert(document)
	if err != nil {
		return err
	}

	return nil
}

func Update(dbName string, coName string, selector interface{}, update interface{}) error {
	session, c, err := getC(dbName, coName)
	if err != nil {
		return err
	}
	defer session.Close()

	err = c.Update(selector, update)
	if err != nil {
		return err
	}

	return nil
}

func Remove(dbName string, coName string, selector interface{}) error {
	session, c, err := getC(dbName, coName)
	if err != nil {
		return err
	}
	defer session.Close()

	err = c.Remove(selector)
	if err != nil {
		return err
	}

	return nil
}

func Remove_all(dbName string, coName string, selector interface{}) error {
	session, c, err := getC(dbName, coName)
	if err != nil {
		return err
	}
	defer session.Close()
	_, err = c.RemoveAll(selector)
	if err != nil {
		return err
	}

	return nil
}

func Find(dbName string, coName string, query interface{}, selector interface{}, result interface{}) error {
	session, c, err := getC(dbName, coName)
	if err != nil {
		return err
	}
	defer session.Close()

	err = c.Find(query).Select(selector).All(result)
	if err != nil {
		return err
	}

	return nil
}

func FindOne(dbName string, coName string, query interface{}, selector interface{}, result interface{}) error {
	session, c, err := getC(dbName, coName)
	if err != nil {
		return err
	}
	defer session.Close()

	err = c.Find(query).Select(selector).One(result)
	if err != nil {
		return err
	}

	return nil
}

func FindPage(dbName string, coName string, query interface{}, selector interface{}, sortQuery string, from int, count int, result interface{}) error {
	session, c, err := getC(dbName, coName)
	if err != nil {
		return err
	}
	defer session.Close()

	err = c.Find(query).Sort(sortQuery).Skip(from).Limit(count).Select(selector).All(result)

	return err
}

func Count(dbName string, coName string, query interface{}) (int, error) {
	session, c, err := getC(dbName, coName)
	if err != nil {
		return 0, err
	}
	defer session.Close()

	count, err := c.Find(query).Count()
	if err != nil {
		return 0, err
	}

	return count, nil
}

func FindAndModify(dbName string, coName string, query interface{}, change mgo.Change, result interface{}) error {
	session, c, err := getC(dbName, coName)
	if err != nil {
		return err
	}
	defer session.Close()

	_, err = c.Find(query).Apply(change, result)
	if err != nil {
		return err
	}

	return nil
}
