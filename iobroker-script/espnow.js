const SerialPort = require('serialport')
const Delimiter = require('@serialport/parser-delimiter')
const port = new SerialPort('/dev/ttyUSB0', {
    baudRate: 115200
})

function parseReceived(data, cb) {
    let parts = data.split(';');
    parts.pop();
   let result = {};
    let response = parts.map((item) => {
        let sub = item.split('=');
        result[sub[0]] = sub[1];
    })

    return cb(result);
}

const parser = port.pipe(new Delimiter({ delimiter: '\r\n' }))

port.on('error', err => console.error(err));

parser.on('data', (data) => {
    console.log('Received Data');
    console.log(data.toString());
    
    parseReceived(data.toString(), function(received){
        console.log(received);
    let mac = received.mac.replace(/:/g, '-');
    let data = received.rx;
        getState(`espnow.0.${mac}`, (state) => {
            if(state == null) {
                createState(`espnow.0.${mac}`, null, true, () => {
                    setState(`espnow.0.${mac}`, data);
                });
            } else {
                setState(`espnow.0.${mac}`, data);
            }
        })
    });
});

console.log('booted');
