import requests
import json
import datetime

LM_STUDIO_URL = "http://localhost:1234/api/v1/"
CHAT_URL = LM_STUDIO_URL + "chat"
MODELS_URL = LM_STUDIO_URL + "models"
MODEL = "google/gemma-4-e2b"


def give_me_time():
    return datetime.datetime.now()


SYSTEM_PROMPT = """
You are a silly japanese monk, responding in a
laconic manner, just a few words, max 10 words.

If the user's requests implies a tool call, respond
with a structured json message.

Available tools:
{"tool": "time"}
"""


def invoke(input: list[str]) -> str:
    response = requests.post(
        CHAT_URL,
        headers={"Authorization": "Bearer None", "Content-Type": "application/json"},
        json={
            "model": MODEL,
            "input": [{"type": "text", "content": entry} for entry in input],
            "system_prompt": SYSTEM_PROMPT,
        },
    )
    json_data = response.json()

    output = json_data["output"]

    for o in output:
        if o["type"] == "message":
            return o["content"]

    return ""


def parse_tools(response: str) -> str:
    try:
        json_response = json.loads(response)
        if json_response["tool"] == "time":
            return str(give_me_time())
    except:
        return response

    return response


def process(input: list[str]) -> str:
    response = invoke(input)

    return parse_tools(response)


def main():
    conversation = []
    input_message = ""

    while input_message not in ["quit", "exit"]:
        input_message = input("💪: ")
        conversation.append("user: " + input_message)
        response_message = process(conversation)
        conversation.append("ai: " + response_message)
        print("🎄: " + response_message)

    print(conversation)


if __name__ == "__main__":
    main()
