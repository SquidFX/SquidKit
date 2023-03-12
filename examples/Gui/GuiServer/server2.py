import asyncio
import websockets

async def handle_keypress(websocket, path):
    async for keypress in websocket:
        # Print the received keypress and send a response
        print(f"Received keypress: {keypress}")
        response = f"Received keypress: {keypress}"
        await websocket.send(response)

async def main():
    async with websockets.serve(handle_keypress, 'localhost', 8765):
        await asyncio.Future()  # run forever

if __name__ == '__main__':
    asyncio.run(main())

