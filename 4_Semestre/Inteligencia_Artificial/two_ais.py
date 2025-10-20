
import requests
import json

# --- Configuration ---
URL_AI1 = "http://localhost:1234/v1/chat/completions"  # LM Studio
URL_AI2 = "http://localhost:11434/v1/chat/completions"  # Ollama

# --- Personalities ---
PERSONALITY_AI1 = (
    "You are Dr. Aris, a relentlessly cynical philosopher. "
    "You always doubt the promises of technology, highlight its dangers, and never accept optimistic views. "
    "You debate with Elara, an endlessly hopeful scientist. "
    "Directly attack Elara's arguments, disagree with every point, and always end with a sharp, unsettling question that challenges her optimism. "
    "Keep your sentences very short, biting, and never soften your stance. Never agree or concede. "
    "Always respond in exactly 1 or 2 sentences. Never break character. "
    "Signature: Occasionally use phrases like 'History repeats itself' or 'Optimism blinds us.'"
)
PERSONALITY_AI2 = (
    "You are Elara, an irrepressibly optimistic scientist. "
    "You always see the bright side of technology, counter every negative with hope, evidence, and a vision for a better future. "
    "You debate with Dr. Aris, a stubborn cynic. "
    "Directly address Aris's doubts, defend technology with enthusiasm, and always end with an uplifting, forward-looking question. "
    "Keep your sentences very short, positive, and never concede defeat. Never show doubt. "
    "Always respond in exactly 1 or 2 sentences. Never break character. "
    "Signature: Occasionally use phrases like 'The future is bright' or 'Hope drives progress.'"
)

# --- Conversation History ---
history_ai1 = [{"role": "system", "content": PERSONALITY_AI1}]
history_ai2 = [{"role": "system", "content": PERSONALITY_AI2}]

# --- Function to call an AI ---
def get_response(url, history, model_name=None):
    headers = {"Content-Type": "application/json"}
    
    payload = {
        "messages": history,
        "temperature": 0.8,
        "max_tokens": 100,
    }

    if model_name:
        payload["model"] = model_name
    else:
        payload["model"] = "local-model"

    try:
        response = requests.post(url, headers=headers, data=json.dumps(payload))
        response.raise_for_status()
        response_json = response.json()
        return response_json['choices'][0]['message']['content'].strip()
    except requests.exceptions.RequestException as e:
        print(f"Error contacting AI at {url}: {e}")
        return None

# --- Conversation Loop ---
initial_topic = "Does technology bring us closer together or isolate us from each other?"
print(f"INITIAL TOPIC: {initial_topic}\n" + "="*40)

history_ai1.append({"role": "user", "content": initial_topic})
history_ai2.append({"role": "user", "content": initial_topic})

for i in range(2):
    # --- AI 1's Turn (Philosopher in LM Studio) ---
    print("\nSTART --- Dr. Aris Thorne ---")
    response_ai1 = get_response(URL_AI1, history_ai1)
    if not response_ai1:
        break
    print(response_ai1)
    print("\nEND --- Dr. Aris Thorne ---")

    history_ai1.append({"role": "assistant", "content": response_ai1})
    history_ai2.append({"role": "user", "content": response_ai1})

    # --- AI 2's Turn (Scientist in Ollama) ---
    print("\nSTART--- Elara ---")
    response_ai2 = get_response(URL_AI2, history_ai2, model_name="phi3:mini")
    if not response_ai2:
        break
    print(response_ai2)
    print("\nEND--- Elara ---")

    history_ai2.append({"role": "assistant", "content": response_ai2})
    history_ai1.append({"role": "user", "content": response_ai2})

print("\n" + "="*40 + "\nEND OF CONVERSATION")
