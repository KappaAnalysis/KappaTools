def mp(x):
	print type(x), x
inputs = filter(lambda x: not x.startswith("__"), dir(runtime))
print inputs
for x in inputs:
	obj = getattr(runtime, x)
	print type(obj), x, "=", obj

print "="*10

config = Config()
config.test = [1,2,3]
config.dicttest = {1:2, 3:4}
config.dicttest1 = {"HALLO":2, "WELT":4}
config.string = "HALLO WELT!"
config.obj = ("NAME", {"key1": "value1", "key2": "value2"}, [12, 23, 34])
config.pair = (12.4, "DOUBLE")
config.pairlist = [(1.3, 2.1), (4.8, 6.4), (5.7, 8.9)]

config.xyz = Config()
config.xyz.a = "A"
config.xyz.b = "b"
print config.__dict__

print "="*10
print "CONFIG FILE WAS EXECUTED!"
print "="*10
