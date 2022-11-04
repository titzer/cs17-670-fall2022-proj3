const fs = require("fs");

var args = process.argv.slice(3);
const filename = process.argv[2];
const bytes = fs.readFileSync(filename);
const wasm = new WebAssembly.Module(bytes);

// The imports for Wee-O-Wasm, implemented in JavaScript.
const imports = {weewasm: {
    puti: v => process.stdout.write("" + (v | 0)),
    putd: v => process.stdout.write("" + (+v)),
    // TODO: puts requires the module to export its memory, which is currently disallowed in WeeWasm.

    // Allocates a new WeeWasm object.
    "obj.new": () => new WeeObject(),
    // Gets a property from a WeeWasm object, given the key.
    "obj.get": function(ref, key) {
	var obj = toWeeObject(ref);
	if (key == null) throw new Error("null key");
	var v;
	if (key instanceof F64Box) { // F64s must be unboxed and stored separately
	    v = toElems(obj)[key.val];
	} else {
	    v = obj[key];
	}
	return v == undefined ? null : v;
    },
    // Sets a property from a WeeWasm object, given the key and the value
    "obj.set": function(ref, key, val) {
	var obj = toWeeObject(ref);
	if (key == null) throw new Error("null key");
	if (key instanceof F64Box) { // F64s must be unboxed and stored separately
	    toElems(obj)[key.val] = val;
	} else {
	    obj[key] = val;
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
    if (!(obj instanceof WeeObject)) throw new Error("not a wee object");
    return obj;
}

function toElems(obj) {
    var elems = obj.f64s;
    if (elems == undefined) elems = obj.f64s = new Object();
    return elems;
}

// WeeObjects are distinguished from f64 boxes (and other JS objects)
function WeeObject() {
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
