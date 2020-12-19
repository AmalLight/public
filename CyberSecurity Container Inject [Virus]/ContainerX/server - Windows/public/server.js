"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const express_1 = __importDefault(require("express"));
const path_1 = __importDefault(require("path"));
const app = express_1.default();
app.use('/static', express_1.default.static(path_1.default.join(__dirname)));
app.get('/', (req, res, next) => {
    res.sendFile(path_1.default.join(__dirname + '/index.html'), (err) => {
        if (err) {
            console.log('error occurred for "html send file"');
        }
        else
            console.log('html send file done without errors');
    });
});
app.listen(8080, () => { console.log('server started'); });
