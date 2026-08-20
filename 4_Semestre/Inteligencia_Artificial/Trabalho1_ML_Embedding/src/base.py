import numpy as np
from sentence_transformers import SentenceTransformer
from sklearn.preprocessing import normalize
import csv

schools = [
    'abjuration', 'abjuration',
    'necromancy', 'necromancy',
    'evocation', 'evocation',
    'transmutation', 'transmutation',
    'illusion', 'illusion',
    'enchantment', 'enchantment',
    'divination', 'divination',
    'conjuration', 'conjuration'
]

descriptions = [
    "For the duration, you hide a target that you touch from divination magic. The target can be a willing creature or a place or an object no larger than 10 feet in any dimension. The target can't be targeted by any divination magic or perceived through magical scrying sensors.",
    "A shimmering field surrounds a creature of your choice within range, granting it a +2 bonus to AC for the duration.",
    "You touch a creature that has died within the last minute. That creature revives with 1 Hit Point. This spell can’t revive a creature that has died of old age, nor does it restore any missing body parts.",
    "A creature that you can see within range makes a Constitution saving throw, taking 8d8 Necrotic damage on a failed save or half as much damage on a successful one. A Plant creature automatically fails the save.",
    "You unleash a wave of thunderous energy. Each creature in a 15-footCubeoriginating from you makes a Constitution saving throw. On a failed save, a creature takes 2d8 Thunder damage and is pushed 10 feet away from you. On a successful save, a creature takes half as much damage only.",
    "A bright streak flashes from your pointing finger to a point you choose within range and then blossoms with a low roar into an explosion of flame. Each creature in a 20-foot-radius sphere centered on that point must make a Dexterity saving throw. A target takes 8d6 fire damage on a failed save, or half as much damage on a successful one.",
    "Until the spell ends, you control any water inside an area you choose that is aCubeup to 100 feet on a side, using one of the following effects. As aMagicaction on your later turns, you can repeat the same effect or choose a different one.",
    "Until the spell ends, one willing creature you touch has Resistance to Bludgeoning, Piercing, and Slashing damage.",
    "You create a sound or an image of an object within range that lasts for the duration. See the descriptions below for the effects of each. The illusion ends if you cast this spell again.",
    "A Large quasi-real, horselike creature appears on the ground in an unoccupied space of your choice within range. You decide the creature's appearance, but it is equipped with a saddle, bit, and bridle.",
    "You place acurseon a creature that you can see within range. Until the spell ends, you deal an extra 1d6 Necrotic damage to the target whenever you hit it with an attack roll.",
    "You give a verbal command to a creature that you can see within range, ordering it to carry out some service or refrain from an action or a course of activity as you decide.",
    "For the duration, you sense the presence of magic within 30 feet of you. If you sense magic in this way, you can use your action to see a faint aura around any visible creature or object in the area that bears magic, and you learn its school of magic, if any. The spell can penetrate most barriers, but it is blocked by 1 foot of stone, 1 inch of common metal, a thin sheet of lead, or 3 feet of wood or dirt.",
    "You create an invisible, magical eye within range that hovers in the air for the duration. You mentally receive visual information from the eye, which has normal vision anddarkvisionout to 30 feet. The eye can look in every direction.",
    "A storm cloud appears at a point within range that you can see above yourself. It takes the shape of aCylinderthat is 10 feet tall with a 60-foot radius. When you cast the spell, choose a point you can see under the cloud.",
    "You summon a spirit that assumes the form of an unusually intelligent, strong, and loyal steed, creating a long-lasting bond with it. Appearing in an unoccupied space within range, the steed takes on a form that you choose: awarhorse, apony, acamel, anelk, or amastiff."
]

def load():
    data = np.load('data/feiticos_embeddings.npz')

    train_embeddings = data['train_embeddings']
    validation_embeddings = data['validation_embeddings']
    test_embeddings = data['test_embeddings']

    train_label = data['train_label']
    validation_label = data['validation_label']
    test_label = data['test_label']

    # Combinar treino e validação para validação cruzada
    train_val_embeddings = np.vstack([train_embeddings, validation_embeddings])
    train_val_label = np.concatenate([train_label, validation_label])

    return train_val_embeddings, train_val_label, test_embeddings, test_label

def get_sentence_transformer(model_name: str = 'sentence-transformers/all-MiniLM-L6-v2') -> SentenceTransformer:
    return SentenceTransformer(model_name)

def prediction(school, description, best_model, transform_model):
    sen_embed = transform_model.encode(description, convert_to_numpy=True)

    # Normalizar o embedding com L2
    sen_embed_normalized = normalize([sen_embed], norm='l2')

    prediction = best_model.predict(sen_embed_normalized)

    if prediction[0] == school:
        print(f"[Acerto] O modelo acertou a escola: {prediction[0]}.")
        return 1
    else:
        print(f"[Erro] A escola correta era {school}, o modelo previu: {prediction[0]}.")
        return 0

def interactive_menu(best_model, transform_model, info_str: str):
    acertos = 0
    total = 0

    while True:
        print("\n-----OPÇÕES-----")
        print("1 - Testar para um input personalizado.")
        print("2 - Testar para dados pré-feito (8 casos do teste).")
        print("3 - Testar para dados pré-feito (todos casos do teste).")
        print("4 - Sair")
        print("Escolha:", end=" ")
        resp = input()
        print()

        if resp == "1":
            school = input("Digite a escola: ")
            description = input("Digite a descrição do feitiço: ")

            print(info_str)
            acertos += prediction(school, description, best_model, transform_model)
            total += 1

        elif resp == "2":
            print(info_str)
            for i in range(len(schools)):
                acertos += prediction(schools[i], descriptions[i], best_model, transform_model)
                total += 1

        elif resp == "3":
            print(info_str)
            
            with open('data/separated/feiticos_test.csv', encoding='utf-8') as csvfile:
                reader = csv.DictReader(csvfile)
                for row in reader:
                    school = row['escola']
                    description = row['descricao']

                    acertos += prediction(school, description, best_model, transform_model)
                    total += 1

        elif resp == "4":
            accuracy = acertos / total if total else 0.0
            print(f"Taxa de acerto total: {accuracy:.2%}.")
            print("Saindo.")
            return
        
        else:
            print("Erro no input.")
