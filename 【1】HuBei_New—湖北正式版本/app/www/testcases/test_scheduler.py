import unittest
import urllib2
import urllib
import json
import time

class TestSchedulerApi(unittest.TestCase):

    def setUp(self):
        pass

    def testQueryConfig(self):
        response = urllib2.urlopen('http://192.168.2.200/api/v1/scheduler/config')
        html = response.read()
        config = json.loads(html)
        print(config)

    def testChangeConfig(self):
        url = 'http://192.168.33.10/api/v1/scheduler/config'
        values = {}
        values["baseconfig"] = {}
        values["psamconfig"] = []
        values["rfconfig"] = []
        values["baseconfig"]["routeinfo"] = "0406"
        values["baseconfig"]["beaconid"] = "A6000144"
        values["baseconfig"]["sleeptime"] = 1
        values["baseconfig"]["parallel_trade"] = 3
        psam1 = {}
        psam1["psamid"] = 1
        psam1["enable"] = True
        psam1["type"] = 1
        psam1["addr"] = "192.168.2.200"
        values["psamconfig"].append(psam1)
        psam1 = {}
        psam1["psamid"] = 1
        psam1["psamid"] = True
        psam1["type"] = 1
        psam1["addr"] = "192.168.2.200"
        values["psamconfig"].append(psam1)
        psam2 = {}
        psam2["psamid"] = 2
        psam2["enable"] = True
        psam2["type"] = 1
        psam2["addr"] = "192.168.2.200"
        values["psamconfig"].append(psam2)
        psam3 = {}
        psam3["psamid"] = 3
        psam3["enable"] = True
        psam3["type"] = 1
        psam3["addr"] = "192.168.2.200"
        values["psamconfig"].append(psam3)
        psam4 = {}
        psam4["psamid"] = 4
        psam4["enable"] = True
        psam4["type"] = 1
        psam4["addr"] = "192.168.2.200"
        values["psamconfig"].append(psam4)

        rf1 = {}
        rf1["rfsn"] = 1
        rf1["enable"] = True
        rf1["power"] = 20
        rf1["addr"] = "192.168.2.201"
        rf2 = {}
        rf2["rfsn"] = 2
        rf2["enable"] = True
        rf2["power"] = 20
        rf2["addr"] = "192.168.2.202"
        rf3 = {}
        rf3["rfsn"] = 3
        rf3["enable"] = True
        rf3["power"] = 20
        rf3["addr"] = "192.168.2.203"
        rf4 = {}
        rf4["rfsn"] = 4
        rf4["enable"] = True
        rf4["power"] = 20
        rf4["addr"] = "192.168.2.204"
        values["rfconfig"].append(rf1)
        values["rfconfig"].append(rf2)
        values["rfconfig"].append(rf3)
        values["rfconfig"].append(rf4)


        data = json.dumps(values)
        headers = {'Content-Type': 'application/json'}
        req = urllib2.Request(url, data, headers)
        response = urllib2.urlopen(req)
        html = response.read()
        print "receive response :",len(html), str(html)

    def testQueryRuningMode(self):

        response = urllib2.urlopen('http://192.168.33.10/api/v1/scheduler/runingmode')
        html = response.read()
        mode = json.loads(html)
        #print(html)
        print(mode)

    def testSetRuningMode(self):
        url = 'http://192.168.33.10/api/v1/scheduler/runingmode'
        headers = {'Content-Type': 'application/json'}
        values = {}
        values["mode"] = False
        data = json.dumps(values)
        req = urllib2.Request(url, data, headers)
        response = urllib2.urlopen(req)
        html = response.read()
        #mode = json.loads(html)
        print(html)

    def testQueryTradeStat(self):
        response = urllib2.urlopen('http://192.168.33.10/api/v1/scheduler/tradestat')
        html = response.read()
        tradestat = json.loads(html)
        print(tradestat)

    def testClearTradeStat(self):
        url = 'http://192.168.33.10/api/v1/scheduler/tradestat'
        headers = {'Content-Type': 'application/json'}
        values = {}
        values["action"] = "clear"
        data = json.dumps(values)
        req = urllib2.Request(url, data, headers)
        response = urllib2.urlopen(req)
        html = response.read()
        result = json.loads(html)
        print(result)

    def testQueryVersion(self):
        response = urllib2.urlopen('http://192.168.33.10/api/v1/version')
        html = response.read()
        #version = json.loads(html)
        print(html)

    def testRebootReader(self):
        url = 'http://192.168.33.10/api/v1/version'
        headers = {'Content-Type': 'application/json'}
        values = {}
        values["action"] = "reboot"
        data = json.dumps(values)
        req = urllib2.Request(url, data, headers)
        response = urllib2.urlopen(req)
        html = response.read()
        result = json.loads(html)
        print(result)



    def tearDown(self):
        pass


if __name__ == '__main__':
    suite = unittest.TestSuite()
    suite.addTest(TestSchedulerApi('testQueryConfig'))
    #suite.addTest(TestSchedulerApi('testChangeConfig'))
    #suite.addTest(TestSchedulerApi('testSetRuningMode'))
    #suite.addTest(TestSchedulerApi('testQueryRuningMode'))
    #suite.addTest(TestSchedulerApi('testQueryTradeStat'))
    #suite.addTest(TestSchedulerApi('testClearTradeStat'))
    #suite.addTest(TestSchedulerApi('testQueryVersion'))
    #suite.addTest(TestSchedulerApi('testRebootReader'))
    unittest.TextTestRunner().run(suite)
