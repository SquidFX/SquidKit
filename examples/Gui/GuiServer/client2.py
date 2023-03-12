import asyncio
import websockets

async def send_keypresses():
    async with websockets.connect('ws://localhost:8765') as websocket:
        while True:
            # Wait for a keypress from the user
            keypress = await asyncio.get_event_loop().run_in_executor(None, input, "Enter a key: ")

            # Send the keypress to the server
            await websocket.send(keypress)

            # Wait for the server to respond
            response = await websocket.recv()
            print(f"Received response: {response}")

async def main():
    await send_keypresses()

if __name__ == '__main__':
    asyncio.run(main())

