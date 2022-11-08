const fs = require("fs");

var args = process.argv.slice(3);
const filename = process.argv[2];
const bytes = fs.readFileSync(filename);
const wasm = new WebAssembly.Module(bytes);

function log(s) {
//    process.stdout.write(s + "\n");
}

// The imports for Wee-O-Wasm, implemented in JavaScript.
const imports = {weewasm: {
    puti: v => process.stdout.write("" + (v | 0)),
    putd: v => process.stdout.write("" + (+v)),
    // TODO: puts requires the module to export its memory, which is currently disallowed in WeeWasm.

    // Allocates a new WeeWasm object.
    "obj.new": () => new WeakMap(),
    // Gets a property from a WeeWasm object, given the key.
    "obj.get": function(ref, key) {
	var obj = toWeeObject(ref);
	log("obj.get(" + obj + ", " + key + ")");
	if (key == null) throw new Error("null key");
	var v;
	if ((typeof key) == "number") {
	    v = obj[key];
	} else if (key instanceof F64Box) { // F64s must be unboxed and stored separately
	    v = getF64s(obj)[key.val];
	} else {
	    v = obj.get(key);
	}
	return v == undefined ? null : v;
    },
    // Sets a property from a WeeWasm object, given the key and the value
    "obj.set": function(ref, key, val) {
	var obj = toWeeObject(ref);
	log("obj.set(" + obj + ", " + key + ", " + val + ")");
	if (key == null) throw new Error("null key");
	if ((typeof key) == "number") {
	    obj[key] = val;
	} else if (key instanceof F64Box) { // F64s must be unboxed and stored separately
	    getF64s(obj)[key.val] = val;
	} else {
	    obj.set(key, val);
	}
    },
    // Converts an i32 into a WeeWasm reference.
    "obj.box_i32": v => v | 0,          // ints are represented as regular JS numbers
    // Converts an f64 into a WeeWasm reference.
    "obj.box_f64": v => new F64Box(+v), // floats are boxed to distinguish from ints
    // Converts a reference back to an i32.
    "i32.unbox": function(v) {
	if (typeof v == "number") return v | 0;
	throw new Error("not an i32");
    },
    // Converts a reference back to an f64.
    "f64.unbox": function(v) {
	if (v instanceof F64Box) return +v.val;
	throw new Error("not an f64");
    },
    // Compare two references for equality.
    "obj.eq": (a, b) => {
	if (a instanceof F64Box) return (b instanceof F64Box) && a.val == b.val;
	return a === b;
    }
}};

function toWeeObject(obj) {
    if (obj == null) throw new Error("null reference");
    if (!(obj instanceof WeakMap)) throw new Error("not a wee object");
    return obj;
}

function getF64s(obj) {
    var elems = obj.f64s;
    if (elems == undefined) elems = obj.f64s = new Object();
    return elems;
}

// F64s represented boxed floats, to distinguish from int
function F64Box(v) {
    this.val = v;
}

const instance = new WebAssembly.Instance(wasm, imports);

var main = instance.exports["main"];

for (var i = 0; i < args.length; i++) {
    var a = args[i];
    if (a.endsWith("d")) { // double
	args[i] = +(a.substring(0, a.length - 1));
    } else { // integer
	args[i] = a | 0;
    }
}

try {
    var result = main(...args);
    if (filename.search("_d.wee.wasm") >= 0) console.log(result.toFixed(6)); // to match C's printf
    else console.log(result);
} catch (e) {
    console.log("!trap");
    process.stderr.write("" + e + "\n");
}
