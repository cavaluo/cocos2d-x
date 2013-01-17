//
// sys properties
//

var sys = sys || {};

Object.defineProperties(sys,
{
	"capabilities" : {
		get : function(){
			var capabilities = {"opengl":true};
			if( sys.platform == 'mobile' ) {
				capabilities["accelerometer"] = true;
				capabilities["touches"] = true;
			} else {
				// desktop
				capabilities["keyboard"] = true;
				capabilities["mouse"] = true;
			}
			return capabilities;
        },
		enumerable : true,
		configurable : true
	},
	"os" : {
		get : function(){
            return __getOS();
        },
		enumerable : true,
		configurable : true
	},
	"platform" : {
		get : function(){
            return __getPlatform();
        },
		enumerable : true,
		configurable : true
	},
	"version" : {
		get : function(){
            return __getVersion();
        },
		enumerable : true,
		configurable : true
	}

});

(function(){

var scheduler = cc.Director.getInstance().getScheduler();

var ScheduleWrapper = cc.Node.extend({
	delegate: null,
	
	ctor: function() {
		this._super();
		cc.associateWithNative(this, cc.Node);
	},

	onTimeout: function(dt) {
		if (this.delegate) {
			this.delegate();
		}
	}
});

// setTimeout
setTimeout = function(fn, millisecond) {
	var node = new ScheduleWrapper();
	node.retain();
	node.delegate = fn;

	scheduler.scheduleCallbackForTarget(node, node.onTimeout, millisecond/1000, 0, 0, false);
	return node;
};

// clearTimeout
clearTimeout = function (id) {
	scheduler.unscheduleAllCallbacksForTarget(id);
	id.release();
};

})();

// function timeoutCB() {
// 	cc.log("I am setTimeout callback");
// 	//setTimeout(timeoutCB, 500);
// }

// var id = setTimeout(timeoutCB, 500);
// clearTimeout(id);