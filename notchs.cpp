#include<bits/stdc++.h>
using namespace std;

enum charms{
    BussolaCaprichosa,
    EnxamedeColecionadores,
    PortadordosSonhos,
    GloriadoMestredoFerrao,
    CogumelocomEsporos,
    InsigniadoDefensor,
    CorpoFirme,
    EspinhosdaAgonia,
    MestredaCorrida,
    CancaodasLarvas,
    CarapacaRobusta,
    ApanhadordeAlmas,
    MestredaEsquiva,
    CoracaoFragil,
    CoracaoInquebravel,
    GananciaFragil,
    GananciaInquebravel,
    SombraAfiada,
    FormadeUnn,
    CancaodasTecelas,
    CriancaGrimm,
    FuriadosCaidos,
    CarapaçadeBaldur,
    UteroBrilhante,
    CoracaodeSangueVital,
    GolpePesado,
    FerraoLongo,
    PedradoXama,
    ElegiadaLarvamosca,
    ForcaFragil,
    ForcaInquebravel,
    DobradordeMagias,
    CorteRapido,
    MarcadeOrgulho,
    NinhodeFlukes,
    FocoRapido,
    NucleodeSangueVital,
    EscudodosSonhos,
    MelodiaDespreocupada,
    DevoradordeAlmas,
    BencaodeJoni,
    SanguedaColmeia,
    FocoProfundo,
    AlmadoRei,
    CoracaoVazio,
    TotalCharms
};

int charmsSlots[] = {
    1, // BussolaCaprichosa
    1, // EnxamedeColecionadores
    1, // PortadordosSonhos
    1, // GloriadoMestredoFerrao
    1, // CogumelocomEsporos
    1, // InsigniadoDefensor
    1, // CorpoFirme
    1, // EspinhosdaAgonia
    1, // MestredaCorrida
    1, // CancaodasLarvas
    2, // CarapacaRobusta
    2, // ApanhadordeAlmas
    2, // MestredaEsquiva
    2, // CoracaoFragil
    2, // CoracaoInquebravel
    2, // GananciaFragil
    2, // GananciaInquebravel
    2, // SombraAfiada
    2, // FormadeUnn
    2, // CancaodasTecelas
    2, // CriancaGrimm
    2, // FuriadosCaidos
    2, // CarapaçadeBaldur
    2, // UteroBrilhante
    2, // CoracaodeSangueVital
    2, // GolpePesado
    2, // FerraoLongo
    3, // PedradoXama
    3, // ElegiadaLarvamosca
    3, // ForcaFragil
    3, // ForcaInquebravel
    2, // DobradordeMagias
    3, // CorteRapido
    3, // MarcadeOrgulho
    3, // NinhodeFlukes
    3, // FocoRapido
    3, // NucleodeSangueVital
    3, // EscudodosSonhos
    3, // MelodiaDespreocupada
    4, // DevoradordeAlmas
    4, // BencaodeJoni
    4, // SanguedaColmeia
    4, // FocoProfundo
    5, // AlmadoRei
    0, // CoracaoVazio
};

int64_t charmsExcludes[TotalCharms] = {};

int main(){
    auto addExcludes = [](charms a, charms b){
        charmsExcludes[a] |= (1ll << b);
        charmsExcludes[b] |= (1ll << a);
    };

    addExcludes(CoracaoFragil, CoracaoInquebravel);
    addExcludes(GananciaFragil, GananciaInquebravel);
    addExcludes(ForcaFragil, ForcaInquebravel);
    addExcludes(CriancaGrimm, MelodiaDespreocupada);
    addExcludes(CoracaoVazio, AlmadoRei);

    vector<int64_t> validCombinationsExact, validCombinationsOver;
    stack<tuple<int64_t, int, int>> q;
    q.emplace(0, 0, 0);
    int m = 11;

    while(q.size()){
        auto [currentCombination, i, qtd] = q.top();
        q.pop();

        if(qtd >= m){
            (qtd > m ? validCombinationsOver : validCombinationsExact).emplace_back(currentCombination);
            continue;
        }

        if(i == CoracaoVazio)
            continue;

        if(!(currentCombination & charmsExcludes[i])){
            q.emplace(currentCombination | (1ll << i), i + 1, qtd + charmsSlots[i]);
        }

        q.emplace(currentCombination, i + 1, qtd);
    }

    int maxSize = ceil(log10(validCombinationsExact.size() + validCombinationsOver.size() + 1));
    printf("%*ld total without overcharged\n", maxSize, validCombinationsExact.size());
    printf("%*ld total with overcharged\n", maxSize, validCombinationsOver.size());
    printf("%*ld in total\n", maxSize, validCombinationsExact.size() + validCombinationsOver.size());
}