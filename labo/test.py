class A:
    def __init__(self, name="土屋"):
        self.name = name 
    def hello(self): 
        print(f"{self.name}さん、こんにちは")
class B(A): 
    def bye(self): 
        print(f"{self.name}さん、さようなら") 
    def hello(self, night=False): 
        if night: 
            print(f"{self.name}さん、こんばんは") 
        else: super().hello()

obj = B()
obj.hello(night=True)