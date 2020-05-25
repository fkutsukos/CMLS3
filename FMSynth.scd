s.boot;


(
SynthDef(\FM,
    {
        arg p3 = 0.5, p4 = 1, p5 = 440, p7 = 0, p8 = 0, t_gate = 0;
        var env1, env2, modFr, out, p6;
        p6 = p5/3;
        env1 = EnvGen.kr(Env([0,p4,p4,0],[p3/5,(p3/5)*4,p3/10]),gate:t_gate);
        env2 = EnvGen.kr(Env([0,((p8-p7)*p6),((p8-p7)*p6),0],[p3/5,(p3/5)*4,p3/10]),gate:t_gate);



        modFr = SinOsc.kr(p6,0,env2+(p7*p6));
        out = SinOsc.ar(p5+modFr,0,env1);
        Out.ar(0,Pan2.ar(out,0));
    }
).add;
)

x = Synth(\FM);
x.set(\p5, 100 , \t_gate, 1);


n = NetAddr.new("127.0.0.1");

OSCFunc({|msg, time, addr, recvPort| x.set(\p5, msg[1], \t_gate, 1)}, '/FM/p5', n);


OSCFunc.trace(bool: true, hideStatusMsg: true);